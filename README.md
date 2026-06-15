# Hiking Routes Management System (C Project)

This is a C program that manages hiking routes and provides various filtering, sorting, and analysis operations.

The program supports:

- Load routes from user input
- Load routes from file
- Print all routes sorted by length (descending)
- Search routes by:
  - Maximum length
  - Location
  - Elevation (uphill/downhill)
  - Altitude range
  - Estimated hiking time
- Save routes to file (sorted by length)

Each route is displayed in both directions (forward and return), unless it is circular.

Each route contains:

- Start location
- End location
- Length (meters)
- Uphill elevation gain
- Downhill elevation loss
- Maximum altitude
- Minimum altitude

Compile using:

```bash
gcc main.c funcs.c -o routes -lm
