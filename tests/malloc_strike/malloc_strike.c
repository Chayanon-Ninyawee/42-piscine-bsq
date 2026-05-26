// malloc_strike.c

#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>

static size_t	g_alloc_count = 0;
static size_t	g_fail_at = 0;
static int		g_failed = 0;

static void	init_fail_at(void)
{
	char	*env;

	if (g_fail_at)
		return ;
	env = getenv("MALLOC_STRIKE");
	if (!env)
		return ;
	g_fail_at = strtoul(env, NULL, 10);
}

static int	should_fail(void)
{
	init_fail_at();
	g_alloc_count++;
	if (g_fail_at && g_alloc_count == g_fail_at)
	{
		g_failed = 1;
		return (1);
	}
	return (0);
}

void	*malloc(size_t size)
{
	static void *(*real_malloc)(size_t) = NULL;

	if (!real_malloc)
		real_malloc = dlsym(RTLD_NEXT, "malloc");
	if (should_fail())
		return (NULL);
	return (real_malloc(size));
}

void	*calloc(size_t nmemb, size_t size)
{
	static void *(*real_calloc)(size_t, size_t) = NULL;

	if (!real_calloc)
		real_calloc = dlsym(RTLD_NEXT, "calloc");
	if (should_fail())
		return (NULL);
	return (real_calloc(nmemb, size));
}

void	*realloc(void *ptr, size_t size)
{
	static void *(*real_realloc)(void *, size_t) = NULL;

	if (!real_realloc)
		real_realloc = dlsym(RTLD_NEXT, "realloc");
	if (should_fail())
		return (NULL);
	return (real_realloc(ptr, size));
}

__attribute__((destructor))
static void	report(void)
{
	if (!g_failed)
		write(2, "NO_FAIL\n", 8);
}
