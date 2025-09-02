# 「chaynOI R1 T4」橙红色的鱼

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/w6fq1o22.png)

## 题目描述

给定 $r,m,s$，问有多少个正整数对 $(fi,sh)$，满足：

+ $ 0 \le fi \le sh \le r$。

+ $\operatorname{popcount}(fi \oplus sh) = m$。

+ $\operatorname{popcount}(fi + sh) = s$。

其中，$\operatorname{popcount}(x)$ 表示 $x$ 的二进制表示中 $1$ 的个数，$\oplus$ 表示异或运算。

为了方便，$r$ 以二进制形式给出。

保证给出的任何数字不含有前导 $0$。

答案对 $998244353$ 取模。

## 说明/提示

### 样例解释：

下文数字为十进制。

$r=7$，有 $(1,5),(2,3),(3,7),(4,5),(4,6),(5,7)$ 六种。

### 数据范围：

记 $n$ 为给出的 $r$ 的长度。 

对于 $100\%$ 的数据，$1 \le n,m,s \le 200$。

**本题采用捆绑测试。**

- Subtask 1(15pts)：$n \le 12$。
- Subtask 2(25pts)：$m,s \le 30$。
- Subtask 3(25pts)：$r=2^n-1$。
- Subtask 4(35pts)：无特殊限制。

## 样例 #1

### 输入

```
111 1 2 ```

### 输出

```
6```

# 题解

## 作者：CuteChat (赞：7)

## 前言

我的同学说遇见了一道数位动态规划题目，一看是唐题，大约 $20$ 秒就口胡了，$20$ 分钟就差不多写完了（可惜前两小时在上课）。

感觉没什么新鲜感，绿也不是不行。

## 题解

如果您并没有数位动态规划的基础，请移步[我的笔记](https://www.luogu.com.cn/article/vyvrgzea)并且查看本题解对应的关键字内容。

这道题首先就能考虑数位动态规划，从高位向低位的顺序进行关于 $x,y$ 的各个位数（以下记 $x',y'$ 分别为 $x,y$ 的第 $i$ 位）的动态规划。

数据范围的量级就很明确地说明了时间复杂度大概是 $O(nms)$ 的。

这样对于前两个条件是可以很好地维护的，具体来说如下：

- 第一个条件直接边动态规划边维护偏序关系即可，毕竟 $x,y,r$ 的第 $i$ 位都是知道的，前两个是在转移的时候枚举出来的，最后一个是输入告诉我们的。
- 第二个条件直接看转移中枚举的 $x \oplus y$ 即可。

第三个条件只需要在状态中加一个进位标记即可，具体来说，定义状态 $jw$ 表示**是否强制钦定第 $i$ 位进位。**

然后就可以开始小力分讨：

- 如果这个标记是有的（**强制要求进位**），那么有两种关于进位的转移：
	- 强制钦定下一位进位，这时就要求 $x+y+1 \ge 2$ 即可，然后加法对应的位置就是 $x\oplus y\oplus 1$。
   - 强制钦定下一位没有进位，这时就要求 $x+y \ge 2$ 即可，然后加法对应的位置就是 $x\oplus y$。
- 如果这个标记是没有的（**强制要求不进位**），那么有两种关于进位的转移：
	- 强制钦定下一位进位，这时就要求 $x+y+1 \le 1$ 即可，然后加法对应的位置就是 $x\oplus y\oplus 1$。
   - 强制钦定下一位没有进位，这时就要求 $x+y \le 1$ 即可，然后加法对应的位置就是 $x\oplus y$。

对于标记的转移，这并不是重点，若有需要，请您参考学习笔记的专栏或代码。

于是按照上述说法进行模拟即可，时间复杂度 $O(nms)$，常数约 $2^5$。

## 细节

由于加法会导致进位，进位会导致位数增长，所以考虑直接在数字加一位 $0$，这样都避免了更多情况的分讨。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

char ss[256];
int n, m, s;
signed  dp[205][205][205][2][2][2];
int dfs(int i, int m, int s, int xy, int yr, int jw) {
	if (m < 0 || s < 0) return 0;
	if (i == n + 1) return jw == 0 && m == 0 && s == 0;
	if (dp[i][m][s][xy][yr][jw] != -1) return dp[i][m][s][xy][yr][jw];
	int ans = 0;
	for (int y = 0; y <= max(yr, (int)(ss[i] - '0')); ++y) {
		for (int x = 0; x <= max(xy, y); ++x) {
			if (jw) { // 强制要求没有本位必须进位
				// 假定下一位没有进位
				if (x + y >= 2) ans += dfs(i + 1, m - (x ^ y), s - (x ^ y), xy || (x != y), yr || (y != (int)(ss[i] - '0')), 0);
				// 假定下一位有进位
				if (x + y + 1 >= 2) ans += dfs(i + 1, m - (x ^ y), s - (x ^ y ^ 1), xy || (x != y), yr || (y != (int)(ss[i] - '0')), 1);
			} else { // 要求不能有进位 
				// 假定下一位没有进位
				if (x + y <= 1) ans += dfs(i + 1, m - (x ^ y), s - (x ^ y), xy || (x != y), yr || (y != (int)(ss[i] - '0')), 0);
				// 假定下一位有进位
				if (x + y + 1 <= 1) ans += dfs(i + 1, m - (x ^ y), s - (x ^ y ^ 1), xy || (x != y), yr || (y != (int)(ss[i] - '0')), 1);
			}
		}
	}
	return dp[i][m][s][xy][yr][jw] = ans % 998244353;
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> (ss + 2) >> m >> s;
	ss[1] = '0';
	n = strlen(ss + 1);
	memset(dp, 255, sizeof(dp));
	cout << dfs(1, m, s, 0, 0, 0) << "\n";
	return 0;
}

```

---

## 作者：tjx114514 (赞：2)

来一个（可能）好写的数位 dp 思路。

首先，下文提到的“每一位”均为二进制下的位。考虑**从低位往高位** DP，设 $dp_{i,j,k,0/1,0/1,0/1}$ 为**从低到高**填到第 $i$ 位时，$fi \oplus sh$ 二进制下有 $j$ 个 $1$，$fi + sh$ 二进制下有 $k$ 个 $1$ ，当前这一位是否被进位，$fi$ 是否大于 $sh$ ，$sh$ 是否大于 $n$ 的方案数。

然后在转移时，枚举 $fi$ 和 $sh$ 在这一位分别是填 $0$ 还是 $1$，用 $\lfloor \frac{fi_i + sh_i + jin_i}{2} \rfloor$ 计算下一位是否进位，用 $(fi_i + sh_i + jin_i) \bmod 2$ 计算 $fi + sh$ 这一位的数字，$fi \oplus sh$ 就不用说了，直接异或就行。

答案为 $dp_{1,0,0,0,0,0}$。

代码用记忆化搜索实现，有注释。~~可能看起来有点屎~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int m,s,d[202],len,f[202][202][202][2][2][2];
inline int dfs(int pos,int num_xor,int num_add,int jin,int limitsh,int limitn){
	if(num_xor>m||num_add>s) return 0;//一个剪枝 
	if(pos==0) return (num_xor==m&&num_add+jin==s&&!limitsh&&!limitn);
	//为什么是 num_add+jin ,因为最高位如果还进位的话，会多一位1。  
	if(f[pos][num_xor][num_add][jin][limitsh][limitn]!=-1) return f[pos][num_xor][num_add][jin][limitsh][limitn];
	long long res=0;
    //枚举fi和sh，其中i代表fi，j代表sh
	for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
			res+=dfs(pos-1,num_xor+(i^j),num_add+(i+j+jin)%2,(i+j+jin)/2,(limitsh?(i>=j):(i>j)),(limitn?(j>=d[pos]):(j>d[pos])));
	return f[pos][num_xor][num_add][jin][limitsh][limitn]=res%mod;
}
int solve(string r){
	memset(d,0,sizeof(d));
	len=r.length();
	for(int i=1;i<=len;i++) d[i]=r[i-1]-'0';
	memset(f,-1,sizeof(f));
	return dfs(len,0,0,0,0,0);
  //在第0位的时候"异或"和"加"1的个数，以及fi、sh、n的值均为0，既然都等于0那么就代表[fi<=sh],[sh<=n]
}
string r;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>r>>m>>s;
	cout<<solve(r);
	return 0;
}
//tlhll
```

---

## 作者：grape_king (赞：2)

## 前言
看了题解区都是直接数位 dp 来写的，这里我就来一篇直接用动态规划求解的题解。

## 题解
首先题目要求的是求解 $0\le fi\le sh\le r$ 中所有满足 $\operatorname{popcount}(fi\oplus sh)=m$ 和 $\operatorname{popcount}(fi+sh)=s$ 的数目。

**Subtask #1**

可以发现我们可以直接对 $fi$ 和 $sh$ 两个数进行暴力枚举，求解的时间复杂度就是 $O(r^2)$ 了。

Code1:
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const i64 mod = 998244353;
i64 dp[205][205][205][2];
i64 qp(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int sum[1 << 13];
void init() {
    for (int i = 1; i < 1 << 13; i++) {
        sum[i] = sum[i ^ (i & -i)] + 1;
    }
}
void solve() {
    string s;
    int p1, p2;
    cin >> s >> p1 >> p2;
    int val = 0;
    for (auto p : s) {
        val *= 2;
        val += p - '0';
    }
    int ans = 0;
    for (int i = 0; i <= val; i++) {
        for (int j = i; j <= val; j++) {
            if (sum[i ^ j] == p1 && sum[i + j] == p2) ans++;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int _ = 1;
    init();
    // std::cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}
```
**Subtask #3**

可以发现，有一条性质是 $r = 2^n - 1$，那么此时可以说明这两个数的二进制位只要不超过 $n$，那么每一位的二进制值就可以是 $(0,1)$ 中的任意一个数，这时候我们就可以列动态规划方程了，首先我们从最低位处理，所以第一维表示处理到二进制位中的第 $i$ 位了，然后第二维表示前 $i$ 位中 $\operatorname{popcount}(fi\oplus sh)$ 的值为 $j$，第三维表示前 $i$ 位中 $\operatorname{popcount}(fi+sh)$ 的值为 $k$，第四维表示第 $i$ 位是否有进位，因为进位会影响下一位高位的 $\operatorname{popcount}(fi+sh)$ 值，所以必须设置这一维，可以发现，我们需要四维来维护这个 $dp$ 方程：$dp_{i,j,k,mar}$，具体的转移不太好用方程展示，详细请看代码。

Code2:
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const i64 mod = 998244353;
i64 dp[205][205][205][2];
i64 qp(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void solve() {
    string s;
    int p1, p2;
    cin >> s >> p1 >> p2;
    int n = s.size();
    reverse(s.begin(), s.end());
    // 先对第一位进行处理
    dp[0][0][0][0]++;
    dp[0][1][1][0]++;
    dp[0][1][1][0]++;
    dp[0][0][1][1]++;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j <= p1; j++) {
            for (int k = 0; k <= p2; k++) {
                for (int mar = 0; mar < 2; mar++) {
                    // 由低位转移到高位
                    // 第一个数字此位为0，第二个数字此位为0
                    (dp[i + 1][j][k][0] += dp[i][j][k][mar]) %= mod;
                    // 第一个数字此位为0，第二个数字此位为1
                    (dp[i + 1][j + 1][k + !mar][mar] += dp[i][j][k][mar]) %= mod;
                    // 第一个数字此位为1，第二个数字此位为0
                    (dp[i + 1][j + 1][k + !mar][mar] += dp[i][j][k][mar]) %= mod;
                    // 第一个数字此位为1，第二个数字此位为1
                    (dp[i + 1][j][k + 1][1] += dp[i][j][k][mar]) %= mod;
                }
            }
        }
    }
    i64 ans = dp[n - 1][p1][p2][0] + dp[n - 1][p1][p2][1];
    ans %= mod;
    i64 inv2 = qp(2, mod - 2);
    ans = ans * inv2 % mod;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int _ = 1;
    // std::cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}
```

**Subtask #4**

我们就没有之前那条特殊性质了，这个时候，我们就需要对这两个数判断是否在前 $i$ 位上大于数字 $r$ 的前 $i$ 位数字，只需要新增加两维即可。

时间复杂度为：$O(nms)$

Code3:
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const i64 mod = 998244353;
i64 dp[205][205][205][2][2][2];
i64 qp(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void solve() {
    string s;
    int p1, p2;
    cin >> s >> p1 >> p2;
    int n = s.size();
    reverse(s.begin(), s.end());
    // 先对第一位进行处理
    dp[0][0][0][0][0][0]++;
    dp[0][1][1][0][0][s[0] == '0']++;
    dp[0][1][1][0][s[0] == '0'][0]++;
    dp[0][0][1][1][s[0] == '0'][s[0] == '0']++;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j <= p1; j++) {
            for (int k = 0; k <= p2; k++) {
                for (int mar = 0; mar < 2; mar++) {
                    for (int is1 = 0; is1 < 2; is1++) {
                        for (int is2 = 0; is2 < 2; is2++) {
                            // 由低位转移到高位
                            // 第一个数字此位为0，第二个数字此位为0
                            (dp[i + 1][j][k][0][s[i + 1] == '1' ? 0 : is1][s[i + 1] == '1' ? 0 : is2] += dp[i][j][k][mar][is1][is2]) %= mod;
                            // 第一个数字此位为0，第二个数字此位为1
                            (dp[i + 1][j + 1][k + !mar][mar][s[i + 1] == '1' ? 0 : is1][is2 | !(s[i + 1] - '0')] += dp[i][j][k][mar][is1][is2]) %= mod;
                            // 第一个数字此位为1，第二个数字此位为0
                            (dp[i + 1][j + 1][k + !mar][mar][is1 | !(s[i + 1] - '0')][s[i + 1] == '1' ? 0 : is2] += dp[i][j][k][mar][is1][is2]) %= mod;
                            // 第一个数字此位为1，第二个数字此位为1
                            (dp[i + 1][j][k + 1][1][is1 | !(s[i + 1] - '0')][is2 | !(s[i + 1] - '0')] += dp[i][j][k][mar][is1][is2]) %= mod;
                        }
                    }
                }
            }
        }
    }
    i64 ans = dp[n - 1][p1][p2][0][0][0] + dp[n - 1][p1][p2][1][0][0];
    ans %= mod;
    i64 inv2 = qp(2, mod - 2);
    ans = ans * inv2 % mod;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int _ = 1;
    // std::cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}
```

---

## 作者：george0929 (赞：1)

数位 DP。

$dp_{i,j,k,0/1,0/1,0/1}$ 表示【只考虑 $fi$ 和 $sh$ 的低 $i$ 位，$\operatorname{popcount}(fi \oplus sh)=j$，$\operatorname{popcount}(fi + sh)=k$，否/是 向上提供进位，$fi$ 否/是 压线，$sh$ 否/是 压线】的方案数。

转移时枚举这一位 $fi$ 和 $sh$ 分别填 $0$ 还是 $1$，再枚举下一位是否向上进位。

答案为 $dp_{n,m,s,0,1,1}+dp_{n,m,s-1,1,1,1}$。

注意题目要求 $fi\le sh$，所以最后要除以 $2$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int ans=0,n,m,s,num[205];
int dp[205][205][205][2][2][2];
int dfs(int pos,int cnt1,int cnt2,int up,int blim1,int blim2){
	if(!pos){
		return cnt1==m&&cnt2==s&&!up;
	}
	if(dp[pos][cnt1][cnt2][up][blim1][blim2]!=-1){
		return dp[pos][cnt1][cnt2][up][blim1][blim2];
	}
	int tlim1=blim1?num[pos]:1;
	int tlim2=blim2?num[pos]:1;
	int res=0;
	for(int fi=0;fi<=tlim1;fi++){//fi 这一位填什么
		for(int sh=0;sh<=tlim2;sh++){//sh 这一位填什么
			for(int nup=0;nup<=1;nup++){//下一位是否向上进位
				if(fi+sh+nup>=2&&!up) continue;//会向上进位，但进位状态为 0，舍去。
				if(fi+sh+nup<2&&up) continue;//不会向上进位，但进位状态为 1，舍去。
				res+=dfs(pos-1,cnt1+(fi^sh),cnt2+((fi+sh+nup)&1),nup,blim1&&(fi==tlim1),blim2&&(sh==tlim2));
				res%=mod;
			}
		}
	}
	return dp[pos][cnt1][cnt2][up][blim1][blim2]=res;
}
#define int long long
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return res;
}
signed main(){
	string r;
	cin>>r>>m>>s;
	n=r.length();
	for(int i=0;i<n;i++){
		num[n-i]=r[i]-'0';
	}
	memset(dp,-1,sizeof(dp));
	int res=dfs(n,0,0,0,1,1);
	memset(dp,-1,sizeof(dp));
	s--;
	res+=dfs(n,0,0,1,1,1);
	res%=mod;
	cout<<res*ksm(2,mod-2)%mod<<endl;
	return 0;
}
```

---

