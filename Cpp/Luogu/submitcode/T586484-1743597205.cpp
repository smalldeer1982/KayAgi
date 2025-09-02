#include <bits/stdc++.h>
using namespace std;

long long n, x;
long long a[100005];

int main(){
    cin >> n >> x;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);

    long long cnt = 0;
    // 对每个 a[i]，通过二分查找是否存在 a[i] + x，若存在则统计重复出现次数
    for(int i = 1; i <= n; i++){
        int l = 1, r = n;
        // 改动①：将 while(l < r) 改成 while(l <= r)，以免错过边界
        while(l <= r){
            int mid = (l + r) / 2;
            long long target = a[i] + x;
            if(a[mid] == target){
                // 找到后，可能存在多个相同值，需要统计重复出现次数
                long long idx = mid;
                long long sameCount = 1;

                // 向左统计相同值
                while(idx - 1 >= 1 && a[idx - 1] == target){
                    sameCount++;
                    idx--;
                }
                // 向右统计相同值
                idx = mid;
                while(idx + 1 <= n && a[idx + 1] == target){
                    sameCount++;
                    idx++;
                }

                cnt += sameCount; // 将所有重复的点都计入
                break;           // 找到并统计完即可退出
            }
            else if(a[mid] > target){
                // 改动②：若 mid 值大于 target，则缩小右边界到 mid - 1
                r = mid - 1;
            }
            else {
                // 否则说明 a[mid] < target，向右搜索
                l = mid + 1;
            }
        }
    }

    // 改动③：直接输出 cnt，无需 (cnt + 1) / 2
    cout << cnt << endl;
    return 0;
}
