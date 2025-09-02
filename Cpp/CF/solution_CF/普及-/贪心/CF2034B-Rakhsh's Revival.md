# Rakhsh's Revival

## 题目描述

### 题目翻译：

给定一个长度为 `n` 的二进制字符串 `s`，其中 `0` 表示弱点，`1` 表示强点。需要确保任意长度为 `m` 的连续区间内至少有一个强点。可以使用一种特殊能力 **Timar**，它能将任意长度为 `k` 的区间内的所有点变为强点（即 `1`）。求解需要使用 **Timar** 的最小次数，使得字符串 `s` 中任意长度为 `m` 的连续区间都至少包含一个 `1`。

## 样例 #1

### 输入

```
3
5 1 1
10101
5 2 1
10101
6 3 2
000000```

### 输出

```
2
0
1```

# 题解

## 作者：chengjindong (赞：1)

[题目](https://www.luogu.com.cn/problem/CF2034B)

贪心。遍历字符串，如果连续 $0$ 的个数达到了 $m$，直接操作，这里需要把后面连续的 $k$ 个位置改成 $1$。每一步都是最优，整体肯定也是。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;
	cin >>t;
	while(t--){
		int n,m,k;
		cin >>n>>m>>k;
		char a[n];
		int ans=0,s=0;
		for(int i=0;i<n;i++){
			cin >>a[i];
		}
		for(int i=0;i<n;i++){
			if(a[i]=='0'){//遇到一个0，s++ 
				s++;
			}else{//间隔了一个1，清空s 
				s=0;
			}
			if(s==m){//m个0了 
				for(int j=i;j<=i+k;j++){//改成1 
					a[j]='1';
				}
				ans++;
			}
		}
		cout<<ans<<endl;//输出 
	} 
	return 0;
}
```

---

## 作者：MingRi_Doctor (赞：0)

## 思路：
我们可以思考贪心。

我们可以想到，如果连续 $m$ 位都是 $0$，说明需要使用特殊能力。这样是最优的，因为此时如果再不使用特殊能力，就无法完成任务。使用能力后记得将 $i$ 设为 $(i+k-1)$，因为剩下 $k-1$ 位都将会是 $1$。
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k; 
string s;
int main(){
    cin>>t;
    for(int i=0;i<t;i++)
    {
    	cin>>n>>m>>k>>s;
    	int a=0,p=0;//a记录使用能力的次数，p记录有连续几位都不是0
    	for(int j=0;j<n;j++)
    	{
    		if(s[j]=='0') p++;
    		else p=0;
    		if(p>=m)//如果连续m位都是0
    		{
    			a++;
    			j+=k-1;
    			p=0;
    		}
    	}
    	cout<<a<<endl;
    }
    
    return 0;
}
```

---

## 作者：_Dynamic_Programming (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2034B)

# 思路

1. **定义**一个 $num$ 表示弱点数量。

2. **遍历**整个数组，如果遇到强点，$num$ 归零，如果遇到弱点，$num$ 加 $1$，这样就可以求出一段区间内弱点的数量。如果 $num$ 等于 $m$，说明这一段区间内需要有一个强点，次数加一。这样这个点之前就不会出现问题了，所以将之后 $k - 1$ 个点改为强点（直接让 $i$ 加 $k - 1$）。

3. **输出**最小次数。

# Code
```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, m, k, ans;
char s[200005];
int main()
{
	cin >> t;
	while(t--)
	{
		cin >> n >> m >> k;
		scanf("%s", s + 1);
		int num = 0;
		ans = 0;
		for(int i = 1; i <= n; i++)
		{
			if(s[i] == '1') num = 0;
			else num++;
			if(num == m)
			{
				num = 0;
				ans++;
				i += k - 1;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：wuyouawa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2034B)

### 思路

考虑贪心。

任意长度为 $m$ 的连续区间内至少有一个强点可理解为“任意长度为 $m$ 的连续区间内不全是弱点”。

那么直接找长度为 $m$ 的连续区间内是不是全是弱点，如果是，则将从起点开始的 $k$ 个字符变成强点，并把下标移到强点后的第一个弱点，还有用一个变量 $ans$ 统计。

最后输出 $ans$ 即可。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k,ans,z;//z是最长的弱点段，ans是答案 
string s;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>k>>s;	
		z=0,ans=0;//清零 
		for(int i=0;i<s.size();i++){		
			if(s[i]=='1')  z=0;//遇到强点置零 
			else  z++;
			if(z==m) //如果到m个了 
			{
				z=0;//重新统计
				ans++;//累加
				i+=k-1;//到强点后的第一个弱点 
			}
		}
		cout<<ans<<endl;//多测换行 
	}
	return 0;
}
```

---

## 作者：programmer330 (赞：0)

## 题解：CF2034B Rakhsh's Revival

### 题意复述

给定一个长度为 $n$ 的二进制字符串 $s$，需要确保任意长度为 $m$ 的连续区间内至少有一个 $1$。可以使用一种特殊能力，它能将任意长度为 $k$ 的区间内的所有点变为 $1$。求解需要使用特殊能力的最小次数，使得字符串 $s$ 中任意长度为 $m$ 的连续区间都至少包含一个 $1$。

### 解题思想

本题可使用**贪心思想**解决。字符串 $s$ 中任意长度为 $m$ 的连续区间都至少包含一个 $1$，意思即为字符串 $s$ 中任意长度为 $m$ 的连续区间不全是 $0$。在输入一个字符串后，从其开头开始遍历，使用 $lx$ 记录连续的 $0$ 的个数，使用 $ans$ 记录操作次数。每当出现连续 $m$ 个 $0$ 的时候，就从这个数开始，将以它为起点、长度为 $k$ 的区间的所有数变为 $1$，同时 $ans$ 的值加 $1$。最后输出 $ans$ 即可。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
signed main(){
	cin>>t;
	while(t--){
		int n,m,k;
		string s;
		cin>>n>>m>>k>>s;
		int l=s.length();
		int lx=0;//lx表示连续的0个数 
		int ans=0;//ans记录答案 
		for(int i=0;i<l;i++){		
			if(s[i]=='1')lx=0;
			else lx+=1;
			if(lx==m){
				i=i+k-1;
				lx=0;
				ans+=1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：HYdroKomide (赞：0)

### 题意：

给定一个 0-1 串，可以把连续 $k$ 个元素推平成 $1$，问最少推平多少次可以使串中没有连续 $m$ 个 $0$。

### 思路：

错误做法：考虑把每个 $0$ 区间分开处理；实际上连续的 $k$ 个元素推平是可以跨区间的，所以必须整体考虑。

考虑贪心的思想，直接从左往右推，当发现有连续 $m$ 个元素后直接从当前位置起，向后推平 $k$ 个位置。这样做我们每一步都一定是最优的，正确。

### 程序如下：

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int N=2e5+5;
int T,n,m,k;
char str[N];
int main(){
	scanf("%d",&T);
	while(T--){
		memset(str,0,sizeof(str));
		scanf("%d%d%d%s",&n,&m,&k,str+1);
		int curcnt=0,ans=0;//维护curcnt作为当前连续0个数
		for(int i=1;i<=n;i++){
			if(str[i]=='1')curcnt=0;
			else{
				curcnt++;
				if(curcnt==m){
					ans++;
					i=i+k-1;
					curcnt=0;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

### THE END

---

## 作者：1234567890sjx (赞：0)

考虑贪心模拟。若当前枚举到位置 $i$ 时恰有 $m$ 个连续的 $0$，则从这个位置开始将后面连续的 $k$ 个位置全部赋值为 $1$。容易证明这是正确的。

时间复杂度为 $O(n)$。

```cpp
char s[N];
void run() {
    int T = read();
    while (T--) {
        int n = read(), m = read(), k = read();
        scanf("%s", s + 1);
        int cnt = 0, sum = 0;
        for (int i = 1; i <= n; ++i) {
            if (s[i] == '0') {
                ++cnt;
                if (cnt >= m) {
                    ++sum;
                    int j, x;
                    for (j = i, x = 1; j <= n && x <= k; ++j, ++x)
                        s[j] = '1';
                    i = j - 1;
                    cnt = 0;
                }
            } else {
                cnt = 0;
            }
        }
        cout << sum << '\n';
    }
}
```

---

## 作者：The_foolishest_OIer (赞：0)

给定一个长度为 $n$ 的 01 二进制串，你要将这个二进制串中所有长度不小于 $m$ 且所有数字都是 $0$ 的子串消除，每次你可以选择一个长度为 $k$ 的区间，并将这个区间内的所有字符都变为 $1$，记为一次操作。

求消除所有长度不小于 $m$ 且所有数字都是 $0$ 的子串的最小操作次数。

贪心。

如果有长度等于 $m$ 且所有数字都是 $0$ 子串，那么肯定是从该子串的右端点开始覆盖最优（不仅消除了这个区间，而且将后面尽可能多的 $1$ 消除了）。

用 $cnt$ 维护当前出现了多少个连续的 $0$ 即可。

时间复杂度：$O(n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int t,n,m,k;
string s;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> n >> m >> k;
	cin >> s;
	int cnt = 0;
	int ans = 0;
	for (int i = 0 ; i < n ; i++){
		if (s[i] == '0') cnt++;
		else cnt = 0; // 断开，也要清零
		if (cnt == m){
			for (int j = i ; j <= min(i + k - 1,n - 1) ; j++)
			    s[j] = '1';
			cnt = 0; // 清零
			ans++; 
		}
	}
	cout << ans << endl;
}
signed main(){
	close();
	cin >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：RAY091016 (赞：0)

### 1. 题目解释

给出一个字符串，你可以使连续的 $k$ 个字符都变为 $1$，求使此字符串每 $m$ 个字符中至少有一个 $1$ 所需的最小操作次数。

### 2. 思路

考虑贪心，显然，我们扫一遍字符串，统计连续的 $0$ 的个数，如果达到 $m$ 就直接操作（因为不管怎样这里必须是 $1$），这样的方法显然最优。

### 3. 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k,cnt,ans;
char a[200200];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		ans=0;
		cnt=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			if(a[i]=='0'){
				cnt++;
			}
			else{
				cnt=0;
			}
			if(cnt==m){
				for(int j=i;j<=i+k-1;j++){
					a[j]='1';
				}
				ans++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

---

