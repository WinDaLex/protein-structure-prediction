test <- function(filename, model) {
    test.data <- read.csv(filename)

    m <- dim(test.data)[1]
    n <- dim(test.data)[2] - 4

    prediction <- compute(model, test.data[,2:n])
    
    p <- prediction$net.result
    num_correct <- 0
    for (i in 1:m) {
        maxm <- max(p[i,])
        for (j in 1:4) {
            if (test.data[i,n+j] == 1 && p[i,j] == maxm) {
                num_correct = num_correct + 1
            }
        }
    }

    print(num_correct / m)
    
    return(num_correct)
}
