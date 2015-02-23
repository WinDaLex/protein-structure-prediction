library(neuralnet)

train <- function(filename, weights=NULL) {
    ptm <- proc.time()

    data <- read.csv(filename)
    m <- dim(data)[1]
    n <- dim(data)[2]

    w <- n - 5

    formula <- paste(paste("V", paste(seq(w+1,w+4), collapse="+V"), sep=""), paste(" ~ V", paste(seq(1,w), collapse="+V"), sep=""), sep="")

    model <- neuralnet(formula, data[1:m%/%10,], hidden=5, startweights=weights)
    print("1/10")
    for (i in 1:8) {
        model <- neuralnet(formula, data[(m%/%10*i)+1:as.integer((m%/%10*(i+1))),], hidden=5, startweights=model$weights)
        cat(i+1)
        print("/10")
    }
    model <- neuralnet(formula, data[as.integer((m%/%10*9)+1):m,], hidden=5, startweights=model$weights)
    print("10/10")

    print(proc.time() - ptm)

    return(model)
}
