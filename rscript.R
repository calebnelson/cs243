setwd("C:/Users/User/Documents/GitHub/cs243")
data = read.csv("data.csv")

for (platform in list("ASUS Laptop", "Raspberry Pi", "Mac")){
  for (dType in list("int", "float", "long", "char")){
    for (test in list("Sum", "Multiply")){
      currentData = data[data$Machine == platform & data$Data.Type == dType & data$Test == test, ]
      bufSize = currentData$Buffer.Size
      time = currentData$Time
      plot(bufSize, time, main=paste(platform, ", ", dType, test))
      abline(lm(time~bufSize), col="red")
    }
  }
}
