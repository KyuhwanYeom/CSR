# CSR
run dijkstra and pagerank algorithm using CSR and compare with gpabs   

# result   
### single thread   
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|
toCSR|0.014615s|0.155632s|44.6702s   
pagerank(with 10 iterations)|0.0564171s|0.577729s|46.107s
dijkstra|5.57013s|   

### parallel
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|
pagerank(with 10 iterations)|0.029903~0.0410054s|0.215217~0.246619s|17.5329s
dijkstra|2.9379s|

### gpabs
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|   
pagerank(with 10 iterations)|0.06861s|0.57092seconds|2.24845s
dijkstra|0.79807s|2.47277s|21.11190s  
