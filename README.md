# CSR
run dijkstra and pagerank algorithm using CSR and compare with gpabs   

# result   
### single thread   
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|
toCSR|0.014615seconds|0.155632seconds|44.6702seconds   
pagerank(with 10 iterations)|0.0564171seconds|0.577729seconds|46.107seconds
dijkstra|5.57013seconds|   

### parallel
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|
pagerank(with 10 iterations)|0.0410054seconds|0.207899seconds|17.5329seconds
dijkstra|109.599seconds

### gpabs
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|   
pagerank(with 10 iterations)|0.06861seconds|0.57092seconds|2.24845seconds     
dijkstra|0.79807seconds|2.47277seconds|21.11190seconds     
