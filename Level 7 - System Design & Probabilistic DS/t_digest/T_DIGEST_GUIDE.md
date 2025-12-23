# T-Digest

A **T-Digest** is a probabilistic data structure for estimating quantiles (like the 90th, 95th, or 99th percentile) with high accuracy, particularly at the tails of a distribution.

## The Problem: Quantile Estimation on Streams
Calculating quantiles on a stream of data is difficult because:
1.  **Memory**: Storing all values to sort them is impossible for large datasets.
2.  **Accuracy**: Simple histograms lose precision, especially for high/low percentiles (the "tails") which are often the most important (e.g., tail latency).

## The T-Digest Solution
T-Digest clusters data points into a collection of **Centroids**. Each centroid is defined by its **mean** and its **weight** (number of points).

1.  **Variable Scale**: Centroids are forced to be smaller (containing fewer points) near the extremes (0 and 1) and can be larger in the middle. This ensures high precision for P1 and P99.
2.  **Compression**: Periodically, the centroids are sorted and merged to maintain a target number of centroids (the compression parameter $\delta$).
3.  **Estimation**: Quantiles are estimated by linearly interpolating between centroids.

## Key Advantages
- **Merging**: Two T-Digests can be merged with very little loss of accuracy. This makes it perfect for parallel/distributed systems.
- **Accuracy**: Much better tail accuracy than previous structures like Q-Digest.
- **Space**: Fixed and small memory footprint (typically a few kilobytes).

## Applications
- **Monitoring**: Real-time percentile calculation for response times, CPU, etc. (e.g., used in Elasticsearch and Prometheus-style metrics).
- **Log Analysis**: Analyzing value distributions across massive log volumes.

## Complexity
| Operation | Average   | Space       |
|-----------|-----------|-------------|
| Add Value | O(log K)  | O(K)        |
| Compress  | O(K log K)| O(K)        |
| Quantile  | O(K)      | O(K)        |

*(K is the number of centroids, usually a few hundred)*
