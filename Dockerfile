# Base image
FROM ubuntu:latest

# Install required dependencies
RUN apt-get update && \
    apt-get install -y build-essential cmake libboost-all-dev libssl-dev libcurl4-openssl-dev

# Set the working directory
WORKDIR /app

# Copy the source code to the working directory
COPY . /app

# Build the C++ application
RUN cmake . && make

# Expose the port on which the server will listen
EXPOSE 8080

# Set the entry point command
CMD ["./your-app-name"]
