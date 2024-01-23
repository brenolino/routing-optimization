cd ..

date > Resultados/saidaGolden_17.txt
echo "====================================================================" >> Resultados/saidaGolden_17.txt
echo "                R E S U L T A D O S    G U L O S O                  " >> Resultados/saidaGolden_17.txt
echo "====================================================================" >> Resultados/saidaGolden_17.txt

for x in $(seq 1 1 1); 
do
  { time ./execGrupo6 Golden_17 0 0 1; } 2>&1 | grep real >> Resultados/saidaGolden_17.txt
done

echo "====================================================================" >> Resultados/saidaGolden_17.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaGolden_17.txt
echo "====================================================================" >> Resultados/saidaGolden_17.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 Golden_17 1 0.05 1000; } 2>&1 | grep real >> Resultados/saidaGolden_17.txt
done;

echo "====================================================================" >> Resultados/saidaGolden_17.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaGolden_17.txt
echo "====================================================================" >> Resultados/saidaGolden_17.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 Golden_17 1 0.1 1000; } 2>&1 | grep real >> Resultados/saidaGolden_17.txt
done;

echo "====================================================================" >> Resultados/saidaGolden_17.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaGolden_17.txt
echo "====================================================================" >> Resultados/saidaGolden_17.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 Golden_17 1 0.15 1000; } 2>&1 | grep real >> Resultados/saidaGolden_17.txt
done;

echo "====================================================================" >> Resultados/saidaGolden_17.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaGolden_17.txt
echo "====================================================================" >> Resultados/saidaGolden_17.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 Golden_17 1 0.3 1000; } 2>&1 | grep real >> Resultados/saidaGolden_17.txt
done;

echo "====================================================================" >> Resultados/saidaGolden_17.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaGolden_17.txt
echo "====================================================================" >> Resultados/saidaGolden_17.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 Golden_17 1 0.5 1000; } 2>&1 | grep real >> Resultados/saidaGolden_17.txt
done;

echo "============================================================================" >> Resultados/saidaGolden_17.txt
echo "R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    R E A T I V O" >> Resultados/saidaGolden_17.txt
echo "============================================================================" >> Resultados/saidaGolden_17.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 Golden_17 2 1 3000; } 2>&1 | grep real >> Resultados/saidaGolden_17.txt
done;