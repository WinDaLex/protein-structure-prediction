prep.feature <- function(primary, pos, window.semisize) {

    RESIDUES <- c('A', 'R', 'N', 'D', 'C', 'E', 'Q', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V')
    result <- c()
    for (offset in -window.semisize:window.semisize) {
        current_residue <- substr(primary, pos + offset, pos + offset)
        for (char in RESIDUES) {
            if (char == current_residue)
                result <- append(result, 1)
            else
                result <- append(result, 0)
        }
    }

    return(result)
}


prep.target <- function(hetc, pos) {
    HETC <-  c('H', 'E', 'T', 'C')
    result <- c()
    current_hetc <- substr(hetc, pos, pos);
    for (char in HETC) {
        if (char == current_hetc)
            result <- append(result, 1)
        else
            result <- append(result, 0)
    }
    return(result)
}


prep.example <- function(example, window.semisize) {
    result <- list()
    for (i in 1:nchar(example$primary)) {
        result <- append(result, prep.feature(example$primary, i, window.semisize))
        result <- append(result, prep.target(example$hetc, i))
    }
    return(result)
}


prep.examples <- function(examples, window.semisize) {
    result <- list()
    for (i in 1:nrow(examples)) {
        result <- append(result, prep.example(examples[i,], window.semisize))
    }
    return(result)
}


product.data.file <- function(examples, filename, window.semisize=4) {
    num.col = (window.semisize * 2 + 1) * 20 + 4
    write.csv(matrix(prep.examples(examples, window.semisize), ncol=num.col, byrow=TRUE), file=filename)
}
