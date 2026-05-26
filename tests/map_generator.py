#!/usr/bin/env python3
import sys
import random

def generate_map(x, y, density):
    empty, obs, full = '.', 'o', 'x'
    
    # Matches the Perl appendix output layout exactly: prints Y (lines/height) first
    sys.stdout.write(f"{y}{empty}{obs}{full}\n")
    
    # Create a weighted pool based on density percentage (0-100)
    pool = [empty] * (100 - density) + [obs] * density
    
    # Generate Y rows, each containing X columns
    for _ in range(y):
        sys.stdout.write(''.join(random.choices(pool, k=x)) + '\n')

if __name__ == "__main__":
    # Expects exactly 3 arguments: X (width), Y (height), and density (0-100)
    if len(sys.argv) != 4:
        print("Usage: python3 map_generator.py <width_x> <height_y> <density_percent>", file=sys.stderr)
        sys.exit(1)
        
    try:
        width_x = int(sys.argv[1])
        height_y = int(sys.argv[2])
        density_percent = int(sys.argv[3])
        
        if density_percent < 0 or density_percent > 100:
            print("Error: Density must be a percentage between 0 and 100", file=sys.stderr)
            sys.exit(1)
            
        generate_map(width_x, height_y, density_percent)
    except Exception as e:
        print(f"Error generating map: {e}", file=sys.stderr)
        sys.exit(1)
