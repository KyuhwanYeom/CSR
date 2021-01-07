# CSR
run dijkstra, pagerank using CSR

# result(single thread)
### ego-Facebook(4039 Nodes)     
toCSR : 0.372187seconds         
pagerank(with 10 iterations) 1.62748seconds    
dijkstra : 109.599seconds    
    
### Slashdot0811(77370 Nodes)
toCSR : 3.3466seconds    
pagerank(with 10 iterations) 17.244seconds 

# result(4 threads)
### ego-Facebook(4039 Nodes)     
toCSR : 0.372187seconds         
pagerank(with 10 iterations) 0.7318seconds    
dijkstra : 48.102seconds    
    
### Slashdot0811(77370 Nodes)
toCSR : 3.3466seconds    
pagerank(with 10 iterations) 7.92427seconds 
