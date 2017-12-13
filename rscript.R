setwd("C:/Users/User/Documents/GitHub/cs243")
data = read.csv("Caleb-243-WithBars2.csv")

for (dType in list("int", "float", "long", "char")){
  par(mfrow=c(2,3))
  for (test in list("Sum", "Multiply")){
    for (platform in list("ASUS Laptop", "Raspberry Pi", "Mac")){
      currentData = data[data$Machine == platform & data$DataType == dType & data$Operation == test, ]
      bufSize = currentData$BufSize
      time = currentData$ops.time
      plot(bufSize, time, main=paste(platform, ", ", dType, test), type="o")
      #abline(lm(time~bufSize), col="red")
    }
  }
}
