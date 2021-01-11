# CSR
run dijkstra and pagerank algorithm using CSR and compare with gpabs   
# Quick Start   
### dijkstra
compile
```
g++ [-fopenmp] [parallel_]dijkstra.cpp CSR_convert.h -o dijkstra.out
```
output
```
./dijkstra.out [text file name] [do_print]
```
### pagerank
compile
```
g++ [-fopenmp] [parallel_]pagerank.cpp CSR_convert.h -o pagerank.out
```
output
```
./pagerank.out [text file name] [do_print] [number of iterations]
```
### shortcut
p   :  print result of dijkstra and pagerank algorithm
n   :  number of iterations

# result   
### single thread   
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|
toCSR|0.014615s|0.155632s|12.5018s   
pagerank(with 10 iterations)|0.0564171s|0.577729s|46.107s
dijkstra|0.250178s|3.6805s|239.351s  

### parallel
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|
pagerank(with 10 iterations)|0.029903~0.0410054s|0.215217~0.246619s|17.5329s
dijkstra|0.112281s|

### gpabs
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|   
pagerank(with 10 iterations)|0.06861s|0.57092s|2.24845s
sssp(delta stepping algorithm)|0.79807s|2.47277s|21.11190s  
