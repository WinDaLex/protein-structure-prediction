sigmoid <- function(z) {
    g = 1.0 / (1.0 + exp(-z))
    return(g)
}

cost.function <- function(theta1, theta2, X, y, lambda) {
    J = 0

    # theta1 has size 5 * 340
    # theta2 has size 4 * 6

    m <- dim(X)[1]
    n <- dim(X)[2]
    a1 = rbind(1, t(X))
    z2 = theta1 %*% a1
    a2 = rbind(1, sigmoid(z2))
    z3 = theta2 %*% a2
    a3 = sigmoid(z3)
    h = a3

    J = 1/m * sum(-y * log(t(h)) - (1-y) * log(1-t(h)))
    J = J + lambda / (2 * m) * sum(theta1[2:5,] ** 2) + sum(theta[2:4,] ** 2)

}

nerual.network <- function(X, y, lambda) {
    m <- dim(X)[1]
    n <- dim(X)[2]
}
