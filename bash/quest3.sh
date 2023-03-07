if [ ! -d "door_configuration" ]; then
  mkdir door_configuration
fi
find . -maxdepth 1 -type f -name "*.conf" -exec mv {} door_configuration \;

if [ ! -d "door_logs" ]; then
  mkdir door_logs
fi
find . -maxdepth 1 -type f -name "*.log" -exec mv {} door_logs \;

if [ ! -d "door_map" ]; then
  mkdir door_map
fi
find . -maxdepth 1 -type f -name "*.1" -exec mv {} door_map \;
mkdir door_configuration
find . -maxdepth 1 -type f -name "*.conf" -exec mv door_configuration \;
mkdir door_logs
find . -maxdepth 1 -type f -name "*.log" -exec mv door_log \;
mkdir door_map
find . -maxdepth 1 -type f -name "*.1" -exec mv door_map \;
