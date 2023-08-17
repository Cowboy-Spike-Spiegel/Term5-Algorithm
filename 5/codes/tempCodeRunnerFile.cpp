int Mining(int** const data, int size) {
    // allocate dp space depend on the last line, and initialize
    int* dp = new int[size];
    dp[0] = data[0][0];
    std::cout  << "\t" << dp[0] << "\n";

    for(int i=1; i < size; i++) {
        // the right
        dp[i] = dp[i-1]+data[i][i];
        // the remain
        for(int j=i-1; j >= 1; j--) {
            dp[j] = Max(dp[j-1], dp[j])+data[i][j];
        }
        // the left
        dp[0] += data[i][0];

        // print
        for(int j=0; j < i; j++)
            std::cout << "\t" << dp[j];
        std::cout  << "\t" << dp[i] << "\n";
    }

    int ans = dp[0];
    for(int i=1; i < size; i++)
        ans = Max(ans, dp[i]);
    delete dp;
    return ans;
}