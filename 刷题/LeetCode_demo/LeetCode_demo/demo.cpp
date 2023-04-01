#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::string;
using std::vector;
using std::count;
using std::find;
using std::ifstream;
using std::ios_base;
using std::istream_iterator;
using std::istreambuf_iterator;

void print_vector(vector<int> nums) {
    cout << endl << "[";
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

int combinationSum4(vector<int>& nums, int target) {
    // 排列数
    vector<int> dp(nums.size() + 1, 0);
    dp[0] = 1;
    for (int i = 0; i <= target; i++) { // 外层容量
        for (int j = 0; j < nums.size(); j++) { // 内层物品
            if (i >= nums[j])  dp[i] += dp[i - nums[j]];
        }
    }
    return dp[nums.size()];
}

int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 104);
    dp[0] = 0;
    for (int i = 0; i < coins.size(); i++) { // 外侧遍历物品
        for (int j = 0; j <= amount; j++) { // 内侧遍历容量
            if (j >= coins[i]) dp[j] = min(dp[j], dp[j - coins[i]] + 1);
        }
        print_vector(dp);
    }
    return dp[amount];
}

int dp_max(vector<int>& nums, int from, int to) {
    vector<int> dp(nums.size() - 1, 0);
    dp[0] = nums[from];
    dp[1] = max(nums[from], nums[from + 1]);

    for (int i = 2; i <= to; i++) { // 遍历物品
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[from + i]);
    }
    return dp[nums.size() - 2];
}

int rob(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    int max12 = max(nums[0], nums[1]);
    if (nums.size() == 2) return max12;
    int max123 = max(max12, nums[2]);
    if (nums.size() == 3) return max123;
    return max(dp_max(nums, 0, nums.size() - 2), dp_max(nums, 1, nums.size() - 1));
}



int main() {
    ifstream inputFile("demo.txt");
    inputFile.unsetf(ios_base::skipws); // 关闭inputFile的
    // 忽略空格标志
    // string fileData((istream_iterator<char>(inputFile)), istream_iterator<char>());
    string fileData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    cout << fileData << endl;
    return 1;
}