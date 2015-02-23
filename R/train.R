library(neuralnet)

train <- function(filename, weights=NULL) {
    ptm <- proc.time()

    data <- read.csv(filename)
    m <- dim(data)[1]
    n <- dim(data)[2]

    w <- n - 5

    formula <- paste(paste("V", paste(seq(w+1,w+4), collapse="+V"), sep=""), paste(" ~ V", paste(seq(1,w), collapse="+V"), sep=""), sep="")

    model <- neuralnet(formula, data, hidden=5, startweights=weights)

    print(proc.time() - ptm)

    return(model)
}
