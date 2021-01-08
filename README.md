# CSR
run dijkstra, pagerank using CSR   

# result   
### single thread   
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|
toCSR|0.372187seconds|3.3466seconds|   
pagerank(with 10 iterations)|1.62748seconds|17.244seconds|
dijkstra|109.599seconds

### 4 threads   
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|
toCSR|0.372187seconds|3.3466seconds|   
pagerank(with 10 iterations)|1.62748seconds|17.244seconds|
dijkstra|109.599seconds

### 8 threads   
algorithm|ego-Facebook(4039 Nodes)|Slashdot0811(77370 Nodes)|LiveJournal(4847571 Nodes)    
---|---|---|---|
toCSR|0.372187seconds|3.3466seconds|   
pagerank(with 10 iterations)|1.62748seconds|17.244seconds|
dijkstra|109.599seconds
