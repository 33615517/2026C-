#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 算法竞赛必备：优化输入输出流，极大提升读写速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // S 存放当前符合前缀要求的子序列的起始下标
    vector<int> S;
    for (int i = 0; i < n; i++) {
        S.push_back(i);
    }

    vector<int> ans; // 存放最终拼出来的答案
    int len = 1;     // 当前正在比对的长度（第几位）

    while (!S.empty()) {
        // next_chars 存放 {当前位的数字, 原数组的起始下标}
        vector<pair<int, int>> next_chars;
        for (int i : S) {
            if (i + len - 1 < n) {
                next_chars.push_back({ a[i + len - 1], i });
            }
        }

        if (next_chars.empty()) break;

        // 核心步骤：按照当前位的值【从大到小】排序
        sort(next_chars.begin(), next_chars.end(), [](const pair<int, int>& x, const pair<int, int>& y) {
            return x.first > y.first;
            });

        bool found_current_level = false;

        // 遍历所有可能的当前位数字
        for (int i = 0; i < next_chars.size(); ) {
            int j = i;
            long long total_subarrays = 0;

            // 统计：如果这一位选 next_chars[i].first，后续一共能产生多少个子数组？
            while (j < next_chars.size() && next_chars[j].first == next_chars[i].first) {
                // 原数组起始位置 idx 向后还能延伸 (n - 当前绝对下标) 个子数组
                int current_idx = next_chars[j].second + len - 1;
                total_subarrays += (n - current_idx);
                j++;
            }

            // 判断第 k 大是否落在当前数字的分支里
            if (k <= total_subarrays) {
                // 确定了！答案的当前位就是它
                ans.push_back(next_chars[i].first);

                // j - i 表示刚好在这里结束（长度恰好为 len）的子数组个数
                // 它们在字典序排列中位于当前组的最底部
                long long strictly_longer = total_subarrays - (j - i);

                if (k <= strictly_longer) {
                    // 答案比当前长度还要长，更新候选下标集合，进入下一轮（长度 len + 1）
                    S.clear();
                    for (int idx = i; idx < j; idx++) {
                        S.push_back(next_chars[idx].second);
                    }
                    found_current_level = true;
                    break;
                }
                else {
                    // 答案恰好就是当前拼出来的前缀，直接输出结果
                    for (int idx = 0; idx < ans.size(); idx++) {
                        cout << ans[idx] << (idx + 1 == ans.size() ? "" : " ");
                    }
                    cout << "\n";
                    return 0; // 完美收工
                }
            }
            else {
                // 第 k 大不在当前数字分支，减去当前分支的数量，去看下一个更小的数字
                k -= total_subarrays;
                i = j;
            }
        }

        if (!found_current_level) break; // 理论兜底，防止死循环
        len++;
    }

    return 0;
}