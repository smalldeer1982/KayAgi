#include <bits/stdc++.h>
using namespace std;
int n,k,a[100005];
bool check(int length){
    long long count = 0; 
    for (int i = 1; i <= n; i++){
        count += a[i] / length; 
        if (count >= k) {
			return true;
		}  
    }
    return false;
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]); 
    }
    int left = 1;
    int right = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > right) {
            right = a[i];  
        }
    }
    int result = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            result = mid; 
            left = mid + 1;  
        }else{
            right = mid - 1;  
        }
    }
    cout << result << endl; 
    return 0;
}