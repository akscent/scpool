
pid=$(pgrep -f ai_door_control.sh)

kill $pid

if ps -p $pid > /dev/null; then
  echo "Process is still running"
else
  echo "Process has been stopped"
fi

