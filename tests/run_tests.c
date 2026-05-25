#include "file_reader.h"
#include "parser_map.h"
#include "types/bsq_map.h"
#include <stdio.h>
#include <stdlib.h>

static void	print_map_data(t_bsq_map map, t_bsq_charset charset)
{
	int	row;
	int	col;

	printf("\n===================================================\n");
	printf("          RAW t_bsq_map STRUCT DATA OUTPUT         \n");
	printf("===================================================\n");
	printf("t_bsq_map {\n    .x = %d,\n    .y = %d,\n", map.x, map.y);
	printf("    .id_arr = [");
	row = -1;
	while (++row < map.y)
	{
		col = -1;
		while (++col < map.x)
		{
			printf("%d", map.id_arr[(row * map.x) + col]);
			if (!(row == map.y - 1 && col == map.x - 1))
				printf(", ");
		}
	}
	printf("]\n}\n===================================================\n");
	printf("        RECONSTRUCTED CHARACTER MAP VISUAL         \n");
	printf("===================================================\n");
	print_bsq_map(map, charset);
	printf("===================================================\n\n");
}
int	main(int argc, char **argv)
{
	t_file_data		file;
	t_bsq_charset	charset;
	t_bsq_map		map;

	if (argc != 2)
	{
		printf("Usage: %s <map_path>\n", argv[0]);
		return (1);
	}
	printf("--- Testing: Target File Execution Check (%s) ---\n", argv[1]);
	file = read_file_all(argv[1]);
	if (!file.data)
	{
		printf("Result: FAILED (Could not read file)\n");
		return (1);
	}
	map = parser_map(file.data, file.size, &charset);
	free(file.data);
	if (map.x <= 0 || map.y <= 0 || !map.id_arr)
	{
		printf("Result: INVALID MAP caught safely (map error).\n");
		return (0);
	}
	printf("Result: VALID MAP parsed successfully!\n");
	print_map_data(map, charset);
	free_bsq_map(&map);
	return (0);
}
