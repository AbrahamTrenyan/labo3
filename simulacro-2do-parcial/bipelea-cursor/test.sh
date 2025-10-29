#!/bin/bash
cd /Users/solvd/Documents/GitHub/labo3/simulacro-2do-parcial/bipelea
rm -f flag.dat
(echo -e "A\nB\nC\nD" | ./ring) &
RING_PID=$!
sleep 1
./equipos
wait $RING_PID 2>/dev/null
