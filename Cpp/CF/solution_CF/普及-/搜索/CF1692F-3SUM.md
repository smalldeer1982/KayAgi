# 3SUM

## 题目描述

给出一个长度为 $n$ 的正整数数组 $a$，判断是否存在三个不同的下标 $i$，$j$，$k$，使 $a_i+a_j+a_k$以数字 $3$ 结尾。

## 说明/提示

在第一组测试数据中，你可以选择 $ i=1 $ , $ j=4 $ , $ k=3 $，那么 $ a_1 + a_4 + a_3 = 20 + 84 + 19 = 123 $，以数字 $3$ 结尾

在第二组测试数据中，你可以选择 $ i=1 $ , $ j=2 $ , $ k=3 $，那么 $ a_1 + a_2 + a_3 = 1 + 11 + 1 = 13 $，以数字 $3$ 结尾

在第三组测试数据中，可以证明不存在这样的 $i$，$j$，$k$。请注意，$ i=4 $ , $ j=4 $ , $ k=4 $ 并不是一个有效的答案，因为尽管 $ a_4 + a_4 + a_4 = 1111 + 1111 + 1111 = 3333 $ 以数字3结尾，但题目中要求选择的三个下标是不同的。

在第四组测试数据中，可以证明不存在这样的 $i$，$j$，$k$。

在第五组测试数据中，你可以选择 $ i=4 $ , $ j=3 $ , $ k=1 $，那么 $ a_4 + a_3 + a_1 = 4 + 8 + 1 = 13 $，以数字 $3$ 结尾

在第六组测试数据中，你可以选择 $ i=1 $ , $ j=2 $ , $ k=6 $，那么 $ a_1 + a_2 + a_6 = 16 + 38 + 99 = 153 $，以数字 $3$ 结尾

## 样例 #1

### 输入

```
6
4
20 22 19 84
4
1 11 1 2022
4
1100 1100 1100 1111
5
12 34 56 78 90
4
1 9 8 4
6
16 38 94 25 18 99```

### 输出

```
YES
YES
NO
NO
YES
YES```

# 题解

## 作者：zct_sky (赞：7)

### Solution:
-----
因为只需要在数组中找到 $3$ 个不同的数（下标不同），它们加起来的和以 $3$ 结尾，那么每个数只有个位有用，然后暴力枚举和结尾为 $3$ 的所有可能，最后逐一判断即可。

和结尾为 $3$ 的所有可能：

- $0+0+3=3$
- $0+1+2=3$
- $1+1+1=3$
- $0+4+9=13$
- $0+5+8=13$
- $0+6+7=13$
- $1+3+9=13$
- $1+4+8=13$
- $1+5+7=13$
- $1+6+6=13$
- $2+2+9=13$
- $2+3+8=13$
- $2+4+7=13$
- $2+5+6=13$
- $3+3+7=13$
- $3+4+6=13$
- $3+5+5=13$
- $4+4+5=13$
- $5+9+9=23$
- $6+8+9=23$
- $7+7+9=23$
- $7+8+8=23$
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
inline ll re(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
inline void wr(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) wr(x/10);
	putchar(x%10+48);
	return;
}
int t,n;
void pr(deque<int> x){
	while(x.size())wr(x.front()),putchar(' '),x.pop_front();
	puts("");
}
int main(){  
	t=re();
	while(t--){
		n=re();
		int a[10]={};
		for(int i=1;i<=n;i++)a[re()%10]++;
		if(a[0]>=1&&a[1]>=1&&a[2]>=1)puts("YES");
		else if(a[0]>=2&&a[3]>=1)puts("YES");
		else if(a[1]>=3)puts("YES");
		else if(a[0]>=1&&a[4]>=1&&a[9]>=1)puts("YES");
		else if(a[0]>=1&&a[5]>=1&&a[8]>=1)puts("YES");
		else if(a[0]>=1&&a[6]>=1&&a[7]>=1)puts("YES");
		else if(a[1]>=1&&a[3]>=1&&a[9]>=1)puts("YES");
		else if(a[1]>=1&&a[4]>=1&&a[8]>=1)puts("YES");
		else if(a[1]>=1&&a[5]>=1&&a[7]>=1)puts("YES");
		else if(a[1]>=1&&a[6]>=2)puts("YES");
		else if(a[2]>=2&&a[9]>=1)puts("YES");
		else if(a[2]>=1&&a[3]>=1&&a[8]>=1)puts("YES");
		else if(a[2]>=1&&a[4]>=1&&a[7]>=1)puts("YES");
		else if(a[2]>=1&&a[5]>=1&&a[6]>=1)puts("YES");
		else if(a[3]>=2&&a[7]>=1)puts("YES");
		else if(a[3]>=1&&a[4]>=1&&a[6]>=1)puts("YES");
		else if(a[3]>=1&&a[5]>=2)puts("YES");
		else if(a[4]>=2&&a[5]>=1)puts("YES");
		else if(a[5]>=1&&a[9]>=2)puts("YES");
		else if(a[6]>=1&&a[8]>=1&&a[9]>=1)puts("YES");
		else if(a[7]>=2&&a[9]>=1)puts("YES");
		else if(a[7]>=1&&a[8]>=2) puts("YES");
		else puts("NO");
	}
    return 0;
}
```

---

## 作者：zbk233 (赞：4)

## 解题思路

容易发现，直接枚举每一个数的速度太慢，所以需要优化。

我们发现结果中个位的 $3$ 只和每个数的个位有关，所以我们选择算出序列中个位为 $[0,9]$ 的数字数，之后枚举 $[0,9]$，找到个位为 $3$ 的数，再判断这些个位有 $3$ 的数是否在序列中存在就行了。

## 参考代码

```cpp
#include<iostream>
using namespace std;
int a[200005];
int b[15];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        int n,flag=0;
        cin>>n;
        for(int i=0;i<=9;i++) b[i]=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            a[i]%=10;
            b[a[i]]++;
        }
        for(int i=0;i<=9;i++){
            for(int j=0;j<=9;j++){
                for(int k=0;k<=9;k++){
                    if((i+j+k)%10!=3) continue;
                    b[i]--;b[j]--;b[k]--;
                    if(b[i]<0||b[j]<0||b[k]<0){
                        b[i]++;b[j]++;b[k]++;
                    }else{
                        flag=1;
                        break;
                    }
                }
                if(flag) break;
            }
            if(flag) break;
        }
        if(flag) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
```


---

## 作者：sjr3065335594 (赞：1)

## 思路

既然是相加后个位是三，那我们只需要保存每个 $a_i$ 的个位就行了。

然后用一个数组来存储每个数字（零到九）在 $a_i$ 的个位出现的次数，最后枚举每种三个一位数相加末尾为三的情况，看是否满足 $a_i$ 的末尾有这三个数。其中要注意，枚举的三个一位数可以重复，所以要计算这三个数重复的次数，不能直接看这个数组是否存在这个数，否则就会导致以下一种情况：枚举的数字是 `1 1 1` ，数组里有只一个一，但会判断为正确。具体见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
int cnt[10];
int same(int i, int j, int k)//这个函数就是看i和j和k重复的个数
{
    return (i==j)+(i==j&&j==k)+1;
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        memset(cnt, 0, sizeof(cnt));
        cin >> n;
        for(int i = 1;i <= n;i++) {
            int x;
            cin >> x;
            cnt[x % 10]++;//存储每个数的个位出现的次数
        }
        bool flag = 0;
        for(int i = 0;i <= 9;i++)//枚举
            for(int j = 0;j <= 9;j++)//枚举
                for(int k = 0;k <= 9;k++)//枚举
                    if((i + j + k) % 10 == 3 && cnt[i] >= same(i, j, k) && cnt[j] >= same(j, i, k) && cnt[k] >= same(k, i, j))//注意不能直接用cnt[i]>=i否则会出现刚才解释的情况
                        flag = 1;
        cout << (flag?"YES":"NO") << endl;
    }
    return 0;//完美结束
}
```


---

## 作者：Otue (赞：1)

# 思路
选择 $3$ 个数字相加使得末尾为 $3$，则只跟这 $3$ 个数字的个位有关！

比如说：序列 $20, 22, 19, 84$ 可以转化为序列 $0,2,9,4$，也就是说只需在 $0,2,9,4$ 中选择 $3$ 个数使得末尾为 $3$ 。

别看这没什么用，这可大大的缩减了 $a_i$ 的值域，使得 $a_i \leq 9$，于是暴力枚举只需要枚举到 $9$ 即可。

然而此时的你：枚举的时候不是跟 $n$ 有关吗？跟 $a_i$ 有啥关系？？

可以用桶来存储 $a_i$ 的个数，暴力枚举的时候 $0\sim9$ 枚举，只需要再桶里面减掉。

# 代码
```c++
#include <bits/stdc++.h>
using namespace std;



const int N = 2e5 + 5; 
int T, n, a[N];
int vis[15], t[N], l;

int main() {
	srand(time(NULL)); 
	cin >> T;
	while (T--) {
		memset(vis, 0, sizeof vis);
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i], vis[a[i] % 10]++;
		bool ok = 0;
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				for (int k = 0; k <= 9; k++) {   //枚举 
					if ((i + j + k) % 10 == 3) {
						vis[i]--, vis[j]--, vis[k]--;
						if (vis[i] >= 0 && vis[j] >= 0 && vis[k] >= 0) {
							cout << "Yes" << endl;
							ok = 1;
							break;
						}
						vis[i]++, vis[j]++, vis[k]++;
					}
				}
				if (ok == 1) break;
			}
			if (ok == 1) break;
		}
	
		if (ok == 0) puts("No");
	}
}
```

---

## 作者：duchengjun (赞：1)

# 题意

给你一个数 $n$ 和一个长度为 $n$ 的数组 $a$，问你有没有三个不同位置的数的和的个位数为 3。

# 分析

我在考试时，看到这题就直接蒙圈了，怎么求？三重循环？DP？DFS？

怎么办？我突然灵机一动，想到了：

控制个位数是 3 的因素只有这 3 个数的个位数，所以我们把所有的 $a_i$ 全都模上 10，然后判断哪 3 个数可以构成。

哪怎么判断呢？

我们只需要求的是可不可以，那么我们把所有的数（取过模的数）都求一下个数，然后判断当哪一个数字个数为多少，另一个的个数为多少，最后一个的个数有多少时就可以满足。

哪怎么知道数的个数为多少时可以满足呢？

我只能说暴力您不会吗，我直接 DFS！！！

```cpp
void dfs(int tot,int cur,int t){
	if(tot>t)return;
	if(cur>3){
		if(tot==t)
			for(int i=1;i<=3;i++)
				a[i].push_back(ans[i]);
		return;
	}
	for(int i=0;i<=9;i++){
		ans[cur]=i;
		dfs(tot+i,cur+1,t);
	}
}
```

然后再求一下个数：

```cpp
dfs(0,1,3),dfs(0,1,13),dfs(0,1,23);
for(int i=0;i<a[1].size();i++){
	t[i][a[1][i]]++;
	t[i][a[2][i]]++;
	t[i][a[3][i]]++;
}
```

您会惊奇地发现一共有 100 种组合方式，很整，看看代码吧。

# CODE

```cpp
// Problem:F. 3SUM
// From:CF
// URL:https://codeforces.com/problemset/problem/1692/F
// Author:dcj666

#include<bits/stdc++.h>
using namespace std;
int T,n;
int vis[10];
int t[110][10];
int ans[5];
vector<int>a[5];
void dfs(int tot,int cur,int t){
	if(tot>t)return;
	if(cur>3){
		if(tot==t)
			for(int i=1;i<=3;i++)
				a[i].push_back(ans[i]);
		return;
	}
	for(int i=0;i<=9;i++){
		ans[cur]=i;
		dfs(tot+i,cur+1,t);
	}
}
int main(void){
	std::ios::sync_with_stdio(false);
	dfs(0,1,3),dfs(0,1,13),dfs(0,1,23);
	for(int i=0;i<a[1].size();i++){
		t[i][a[1][i]]++;
		t[i][a[2][i]]++;
		t[i][a[3][i]]++;
	}
	cin>>T;
	while(T--){
		memset(vis,0,sizeof(vis));
		cin>>n;
		for(int i=1,x;i<=n;i++){
			cin>>x;
			vis[x%10]++;
		}
		bool w=true;
		for(int i=0;i<100;i++){
			bool ok=true;
			for(int j=0;j<=9;j++)
				if(vis[j]<t[i][j]){
					ok=false;
					break;
				}
			if(ok){
				w=false;
				cout<<"YES\n";
				break;
			}
		}
		if(w)cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：OLE_OIer (赞：1)

## CF1692F 3SUM

这道题是一道很不错的思维题。

题意：给定数列 ${a_n}$，求共有多少个三元组 $(x,y,z)$ 使得 $a_x+a_y+a_z≡3\,(\mathrm{mod}\,10)$。

看到题目，最先想到的应该就是直接三重循环了，但此时的复杂度是 $O(n^3)$ 的，是卡不过去的。于是我们就得想想办法来优化。

注意到若两个数 $x$ 与 $y$ 满足 $x≡y\,(\mathrm{mod}\,10)$，那他们在 $\mathrm{mod}\,10$ 意义下相同。

于是我们就可以开一个桶把数列中所有的数替换成它们 $\mathrm{mod}\,10$ 的余数，然后继续三重循环即可。

代码附上：
```cpp
//CF1692F 3SUM
#include<bits/stdc++.h>
#define int long long
#define elif else if
using namespace std;
void func(){
	int n;cin>>n;
	vector<int>a(n+1,0);//这里数组大小全开 100010 会 MLE，所以可以用动态数组
	int cnt[50]={};//桶
	for(int i=1;i<=n;++i){
		cin>>a[i];
		++cnt[a[i]%10];
	}
	for(int i=0;i<=9;++i){
		for(int j=i;j<=9;++j){
			for(int k=j;k<=9;++k){
				if((i+j+k)%10-3) continue;//如果三个数加起来模 10 不是 3 就直接跳过
				--cnt[i],--cnt[j],--cnt[k];//判断桶之中是否有这三个数
				if(cnt[i]>=0&&cnt[j]>=0&&cnt[k]>=0){//如果满足条件
					cout<<"YES\n";//输出
					return;//一定要结束程序！
				}
				++cnt[i],++cnt[j],++cnt[k];//如果不成立的话一定要把 cnt 数组还原！
			}
		}
	}
	cout<<"NO\n";
}
signed main(){
	ios::sync_with_stdio(false);
	int n;cin>>n;
	for(int i=1;i<=n;++i) func();
	return 0;
}
```
有问题可以在评论区问笔者，笔者会尽快回答的。

---

## 作者：sgl654321 (赞：0)

### 题目大意
- 给定一个含有 $n$ 个数的正整数数组 $a$，每次可以从中选取三个数 $a_i$，$a_j$ 和 $a_k$。$(i\neq j\neq k)$
- 问是否存在一种选取的方法，使得 $a_i+a_j+a_k$ 的个位数字为 $3$。

### 解题思路
首先考虑朴素算法，时间复杂度为 $O(n^3)$，就是枚举出所有的 $a_i$，$a_j$ 与 $a_k$，判断是否存在一种取法使得和的个位数字为 $3$。

之后我们考虑到，和的个位数字只与各个加数的个位数字有关。因此我们可以把所有的加数都模上 $10$。

统计一下 $a$ 数组的各种个位数字，即 $0\sim 9$，都出现了几次。然后可以遍历三次 $0\sim 9$，若它们加起来的个位数字为 $3$，并且在 $a$ 数组中的出现次数比要求的大，那么这种方案就是合法的。

经过这样一改进，我们就把原来的 $n^3$，变成了 $10^3$，一个常数级别的数，大大压缩了时间复杂度。

### 参考代码
注意本题有多组数据。
```cpp
#include<bits/stdc++.h>
using namespace std;
bool p;
long long t,n,a[300010],niubi[20];
char ch;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		p=0;
		memset(niubi,0,sizeof(niubi));
		for(int i=1;i<=n;i++){
			cin>>a[i];
			niubi[a[i]%10]++;
		}
		for(int i=0;i<=9;i++)
			for(int j=0;j<=9;j++)
				for(int k=0;k<=9;k++)
					if((i+j+k)%10==3){
						if(i==j&&i==k){
							if(niubi[i]>=3)p=1;
							continue;
						}
						if(i==j){
							if(niubi[i]>=2&&niubi[k]>=1)p=1;
							continue;
						}
						if(i==k){
							if(niubi[i]>=2&&niubi[j]>=1)p=1;
							continue;
						}
						if(j==k){
							if(niubi[i]>=1&&niubi[j]>=2)p=1;
							continue;
						}
						if(niubi[i]>=1&&niubi[j]>=1){
							if(niubi[k]>=1)p=1; 
						}
					}
		if(p)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：Jerrycyx (赞：0)

## 方法 1：暴力

用三层循环枚举每一种 $i,j,k$ 的选择。

时间复杂度 $O(T \times N^3)$，因为 $ 3 \leq n \leq 2 \cdot 10^5 $，所以明显不可取。

~~代码就不用了，因为我也没用暴力。~~

## 方法 2 根据 $a$ 的个位来枚举

**$a_i,a_j,a_k$ 之和的个位，只取决于这三个数的个位。**

即：如果这三个数的个位的和的个位为 $3$，那么这三个数的和的个位必定为 $3$。

我们可以用 $sum$ 记录每 $a$ 数组内个个位数出现的次数，判断时把 $sum_i,sum_j,sum_k$ 都减 $1$，判断所有元素的出现次数（$0 \sim 9$），然后再判定能否**在这些个位里面选三个，使得它们的和的个位为 $3$**，然后再加回去。

注意事项：

+ 即便是个位相加，它们的和依然可能是两位数，所以还需要再 $\bmod 10$ 一次。

+ 不能只记录是否出现，例如 $1$ 和 $0$ 各出现一次，那么程序会判断 $1,1,1$ 的组合是合法的，但这实际上不合法。

上代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;

int T;
int n;
int sum[15];

int read()	//快读 
{
	int x=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*w;
}
int main()
{
	scanf("%d",&T);
	for(int I=1;I<=T;I++)
	{
		n=read();
		memset(sum,0,sizeof(sum));
		for(int i=1;i<=n;i++)
		{
			int a=read();	//没有必要用数组来存 
			sum[a%10]++;	//sum 记录每个个位出现的次数 
		}
		bool ans=false;
		for(int i=0;i<=9&&!ans;i++)		//!ans 使得找到方案马上退出 
			for(int j=0;j<=9&&!ans;j++)
				for(int k=1;k<=9&&!ans;k++)
				{
					sum[i]--,sum[j]--,sum[k]--;
					if((i+j+k)%10==3&&(sum[i]>=0&&sum[j]>=0&&sum[k]>=0))
						ans=true;
					sum[i]++,sum[j]++,sum[k]++;
				}
		printf("%s\n",ans?"YES":"NO");
	}
	return 0;
}
```

## 方法 3：打表出奇迹

我们可以发现，某些固定的三个个位的组合是合法的，那么我们为什么不事先枚举出所有的组合，然后再看数据是否符合条件呢？

核心代码：

```cpp
int s[100][5]={			//s 代表所有可能的组合情况
	{0,0,3},{0,1,2},{0,2,1},{0,4,9},{0,5,8},{0,6,7},{0,7,6},{0,8,5},{0,9,4},
	{1,0,2},{1,1,1},{1,3,9},{1,4,8},{1,5,7},{1,6,6},{1,7,5},{1,8,4},{1,9,3},
	{2,0,1},{2,2,9},{2,3,8},{2,4,7},{2,5,6},{2,6,5},{2,7,4},{2,8,3},{2,9,2},
	{3,1,9},{3,2,8},{3,3,7},{3,4,6},{3,5,5},{3,6,4},{3,7,3},{3,8,2},{3,9,1},
	{4,0,9},{4,1,8},{4,2,7},{4,3,6},{4,4,5},{4,5,4},{4,6,3},{4,7,2},{4,8,1},
	{5,0,8},{5,1,7},{5,2,6},{5,3,5},{5,4,4},{5,5,3},{5,6,2},{5,7,1},{5,9,9},
	{6,0,7},{6,1,6},{6,2,5},{6,3,4},{6,4,3},{6,5,2},{6,6,1},{6,8,9},{6,9,8},
	{7,0,6},{7,1,5},{7,2,4},{7,3,3},{7,4,2},{7,5,1},{7,7,9},{7,8,8},{7,9,7},
	{8,0,5},{8,1,4},{8,2,3},{8,3,2},{8,4,1},{8,6,9},{8,7,8},{8,8,7},{8,9,6},
	{9,0,4},{9,1,3},{9,2,2},{9,3,1},{9,5,9},{9,6,8},{9,7,7},{9,8,6},{9,9,5}
};

for(int i=0;i<90&&!ans;i++)
{
	sum[s[i][0]]--,sum[s[i][1]]--,sum[s[i][2]]--;
	if(sum[s[i][0]]>=0&&sum[s[i][1]]>=0&&sum[s[i][2]]>=0)
		ans=true;
	sum[s[i][0]]++,sum[s[i][1]]++,sum[s[i][2]]++;
}
```

附上打表程序：

```cpp
for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
			for(int k=1;k<=9;k++)
				if((i+j+k)%10==3)		//如果满足条件则输出
					printf("{%d,%d,%d},",i,j,k);
		printf("\n");
	}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

首先，维护一个长度为 $10$ 的 `cnt` 数组，用于记录输入数据中每个个位的出现次数。

然后，枚举三个 $0$ 到 $9$ 的数字，代表我要选择的 $3$ 个数，个位分别是多少。

然后，在确定三个数字的个位后，检查 `cnt` 数组有没有足够的数字。如果有，则有解。如果没有，则继续枚举。

### 二、代码

```cpp
#include<cstdio>
using namespace std;
int t;
int n;
int a[200005];
int cnt[10];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		for(int i=0;i<10;i++)
		{
			cnt[i]=0;
		}
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			cnt[a[i]%10]++;//计数
		}
		bool ans=false;//有解吗？
		for(int i=0;i<10&&!ans;i++)//枚举
		{
			for(int j=i;j<10&&!ans;j++)
			{
				for(int k=j;k<10;k++)
				{
					cnt[i]--;//使用这种方法判断cnt数组对于这个枚举是否足够
					cnt[j]--;
					cnt[k]--;
					bool flag=true;
					if(cnt[i]<0||cnt[j]<0||cnt[k]<0)//不足
					{
						flag=false;
					}
					if(flag&&(i+j+k)%10==3)//有解
					{
						ans=true;
						//printf("%d %d %d\n",i,j,k);
						break;
					}
					cnt[i]++;//记得复位
					cnt[j]++;
					cnt[k]++;
				}
			}
		}
		printf(ans?"YES\n":"NO\n");
	}
	return 0;
}

```


---

## 作者：yeshubo_qwq (赞：0)

## Description

给定 $n$ 个数，要求任意选择三个数，使得这三个数的和的个位是 $3$，问是否有一种可行方案。

## Solution

$n$ 的范围达到了 $2 \times 10^5$，$O(n^3)$ 肯定会超时，考虑如何优化。

因为最后的结果只看个位，所以可以将所有 $a_i \pmod {10}$。

个位只可能是 $0 \sim 9$，可以将每个数字的数量与 $3$ 取小（因为只选择三个数），然后代替原 $a$ 数组。

最多有 $10 \times 3 = 30$ 个数，枚举就不会超时了。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,x,c[10],i,j,k,a[31],tot;
inline void read(int &x){
	char c=getchar();
	while (!isdigit(c)) c=getchar();
	x=(c^48);c=getchar();
	while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
}
bool check(){
	for (i=1;i<=tot;i++)
		for (j=i+1;j<=tot;j++)
			for (k=j+1;k<=tot;k++)
				if ((a[i]+a[j]+a[k])%10==3)
					return true;
	return false;
}
int main(){
	read(T);
	while (T--){
		read(n);
		for (i=0;i<=9;i++) c[i]=0;
		tot=0;
		for (i=1;i<=n;i++){
			read(x),x%=10;
			if (++c[x]<=3) a[++tot]=x;
		}
		if (check()) putchar('Y'),putchar('E'),putchar('S');
		else putchar('N'),putchar('O');
		putchar('\n');
	}
	return 0;
}

```


---

## 作者：__vector__ (赞：0)

## 题目翻译  
给你一个 $n$ 个元素的数列 $a$。  
问是否可以选择 $3$ 个**不同**的下标 $i,j,k$，使得 $a_i+a_j + a_k$ 的个位是 $3$。  
## 解法  
换一种思路，可以枚举所有的数字组合，对于每一种组合判断是否在 $a$ 数组中出现过。  
虽然运算次数达到了 $10^{27}$，但是可以进行优化。   
可以发现最终答案的个位只和 $a_i,a_j,a_k$ 的个位有关。  
也就是说只需要枚举所有的个位组合，然后判断这样的组合在数列 $a$ 的有没有出现就行了。  
直接看代码应该更清楚  
## 代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Main
{
	const int maxn=2e5+5;
	int t,n;
	int im[10];//一个桶，im[i] 代表有 im[i] 个元素的个位等于 i
	int a[maxn];
	void main()
	{
		scanf("%d",&t);
		while(t--)
		{
			memset(im,0,sizeof(im));
			scanf("%d",&n);
			for(int i=1;i<=n;i++)
			{
				scanf("%d",&a[i]);
				im[a[i]%10]++;//a[i]的个位出现次数++
			}
			bool flag=0;
			for(int i=0;i<=9;i++)
			{
				if(!im[i])continue;
				for(int j=0;j<=9;j++)
				{
					if(i==j)
					{
						if(im[j]<2)continue;
					}
					else
					{
						if(!im[j])continue;
					}//a 中没出现过，跳过该组合
					for(int k=0;k<=9;k++)
					{
						if(i==j&&j==k)
						{
							if(im[k]<3)continue;
						}
						if(i==k||j==k)
						{
							if(im[k]<2)continue;
						}
						else
						{
							if(!im[k])continue;
						}//a 中没出现过，跳过该组合
						if((i+j+k)%10==3)
						{//该组合是否合法
							printf("Yes\n");
							flag=1;
							break;
						}
					}
					if(flag)break;
				}
				if(flag)break;
			}
			if(!flag)
			{
				printf("No\n");
			}
		}
	}
}
int main()
{
	Main::main();	
	return 0;
}
```


---

## 作者：SSqwq_ (赞：0)

## 题意
给定 $n$ 个数，问能否选定 $a_i,a_j,a_k$ 三个数使得三个数相加的和的末位是 $3$。

## 思路
由于 

$(x \bmod {10})+(y \bmod {10})\equiv (x+y)\pmod{10}$

所以我们只需要存储每个数**个位上的数字**就可以了。

之后，我们可以开一个桶 $s$，其中 $s_i$ 表示原数组中**个位是 $i$ 的数字的个数。**

最后，我们只需进行三层循环枚举所有可能性即可。

## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Mod1=998244353;
const int Mod2=1000000007;
int gcd(int a,int b){return __gcd(a,b);}
int lcm(int a,int b){return a/gcd(a,b)*b;}
const int N=200005;
int a[N],s[N];
void Solve()
{
	//coding here...
	int n;
	memset(s,0,sizeof(s));
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s[a[i]%10]++;//存下个位上的数出现的次数
	}
	for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
		{
			for(int k=0;k<=9;k++)
			{
				s[i]--;
				s[j]--;
				s[k]--;//这里需要注意 i,j,k 不能相同
				if(s[i]>=0&&s[j]>=0&&s[k]>=0&&(i+j+k)%10==3)
				{
					cout<<"YES"<<endl;
					return;
				}
				s[i]++;//回溯
				s[j]++;
				s[k]++;
			}
		}
	}
	cout<<"NO"<<endl;
}
signed main()
{
	ios::sync_with_stdio(false);
	int _=1;
	cin>>_;
	while(_--)
	{
		Solve();
	}
	return 0;
}
```


---

