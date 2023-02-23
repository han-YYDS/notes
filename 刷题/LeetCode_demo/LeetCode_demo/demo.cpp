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

bool canPartition(vector<int>& nums) {
    // 01背包问题 w = 1/2 sum
    int sum = 0;
    for (auto it : nums) {
        sum += it;
    }
    if (sum % 2 == 1) return false;
    int w = 0.5 * sum;

    // 采用一维数组解决背包问题
    vector<int> dp(w + 1, 0);
    // 1.对物品进行for循环
    for (int i = 0; i < nums.size(); i++) {
        // 2.对容积进行遍历 这个要从右往左遍历
            // 三种情况
                // 1. 当前这个物品的重量大于容积 - 直接跳过 - 不进行覆盖
                // 2. 当其这个物品的重量小于容积
                    // 2.1 拥有该物品之后的背包存储 - dp[i-1][j-value[j]]+value[j]
                    // 2.2 没有拥有该物品之后的背包存储 - dp][i-1][j]
            // 对于压缩成一维数组之后 dp[j] = max(dp[j-value]+value, dp[j])
            // 对于第一组,要么满足第一种情况,要么不满足.
        for (int j = w; j >= nums[i]; j--) {
            dp[j] = max(dp[j - nums[i]] + nums[i], dp[j]);
        }
    }
    print_vector(dp);


    if (dp[w] == w) {
        cout << "true" << endl;
        return true;
    }
    cout << "false" << endl;
    return false;
}
 
int lastStoneWeightII(vector<int>& stones) {
    int sum = 0;
    for (auto it : stones) {
        sum += it;
    }
    // 如果sum为奇数,则w去一
    int w = 0.5 * sum;
    cout << "w = " << w << endl;
    cout << "sum =" << sum << endl;
    vector<int> dp(w + 1, 0);
    for (int i = 0; i < stones.size(); i++) {
        for (int j = w; j >= stones[i]; j--) {
            dp[j] = max(dp[j - stones[i]] + stones[i],dp[j]);
        }
        print_vector(dp);
    }
    cout << "dp[w] = "<<dp[w]<< endl;
    print_vector(dp);
    return sum - 2 * dp[w];
}

int func(int n, int target, vector<int>& nums) {
    if (n == 1) {
        if (nums[0] == target && target==0) return 2;
        if (nums[0] == target || nums[0] == target*-1) return 1;
        return 0;
    }
    return func(n - 1, target + nums[n-1], nums) + func(n - 1, target - nums[n-1], nums);
}




int main() {
    vector<int> nums = {7,9,3,8,0,2,4,8,3,9};
   
    int result = func(nums.size(), 0, nums);
    cout << result << endl;
    return 0;
}