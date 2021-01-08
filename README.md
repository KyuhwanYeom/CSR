# CSR
run dijkstra and pagerank algorithm using CSR and compare with gpabs   

# result   
### single thread   
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|
toCSR|0.014615seconds|0.155632seconds|44.6702seconds   
pagerank(with 10 iterations)|0.0564171seconds|0.577729seconds|46.107seconds
dijkstra|5.57013seconds|   

### 4 threads   
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|  
pagerank(with 10 iterations)|0.0343337seconds|0.24118seconds|18.6534seconds
dijkstra|109.599seconds

### 8 threads   
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|
pagerank(with 10 iterations)|0.0410054seconds|0.207899seconds|17.5329seconds
dijkstra|109.599seconds

### gpabs
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|   
gpabs_pagerank(with 10 iterations)|0.0564171seconds|0.577729seconds|46.107seconds     
gpabs_dijkstra|5.57013seconds|     
