library(neuralnet)

train <- function(filename, window.size) {
    ptm <- proc.time()
    w <- window.size * 20
    formula <- paste(paste("V", paste(seq(w+1,w+4), collapse="+V"), sep=""), paste(" ~ V", paste(seq(1,w), collapse="+V"), sep=""), sep="")
    data <- read.csv(filename)


    model <- neuralnet(formula, data, hidden=5)

    print(proc.time() - ptm)

    return(model)
}
