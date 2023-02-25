#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::max;
using std::string;
using std::vector;
using std::count;
using std::find;

void print_vector(vector<int> nums) {
    cout << "[";
    for (auto it : nums) {
        cout << it << ",";
    }
    cout << "]" << endl;
}


int findMaxForm(vector<string>& strs, int m, int n) {
    // 对strs进行解析, 得到 nums0[] 和 nums1[]
    vector<int> nums0(strs.size(), 0);
    vector<int> nums1(strs.size(), 0);
    int i = 0;
    for (auto s : strs)
    {
        for (auto c : s)
        {
            if (c == '1') nums1[i]++;
            if (c == '0') nums0[i]++;
        }
        i++;
    }
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    // 背包问题 双重代价?
    // 这里的逻辑为 三维数组, dp[i][j][k] = max (dp[i-1][j-nums1[i]][k-nums0[i]] + 1, dp[i-1][j][k])
    for (int j = 0; j < strs.size(); j++) {
        // m nums0
        for (int k = m; k >= nums0[j]; k--) {
            for (int l = n; l >=  nums1[j]; l--) {
                dp[k][l] = max(dp[k - nums0[j]][l - nums1[j]] + 1, dp[k][l]);
            }
        }
    }
    int a = 0;
    return dp[m][n];

}


int main() {
    vector<int> nums = {7,9,3,8,0,2,4,8,3,9};
    vector<string> strs = { "10","0001","111001","1","0" };
    int result = findMaxForm(strs, 5, 3);
    cout << result << endl;
    return 0;
}