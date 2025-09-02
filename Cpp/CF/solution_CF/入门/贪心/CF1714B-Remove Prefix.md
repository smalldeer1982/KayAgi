# Remove Prefix

## 题目描述

Polycarp是由一些长度为n的a整数序列组成的（1≤ai≤n）。只有当序列由不同的数字（即不同的数字）组成时，它才能使Polycarp高兴。

为了使他的序列像这样，Polycarp将进行一些移动（可能为零）。

在一个动作中，他可以：

**删除**序列的**第一个（最左侧）元素。**

例如，在一次移动中，序列[3,1,4,3]，将产生由不同数字组成的序列[1,4.3]。

确定他需要移动的最小次数，以便在剩余序列中所有元素都不同。**换句话说，在删除序列中的所有值后，查找给定序列的最小前缀的长度**。

## 样例 #1

### 输入

```
5
4
3 1 4 3
5
1 1 1 1 1
1
1
6
6 5 4 3 2 1
7
1 2 1 7 1 2 1```

### 输出

```
1
4
0
0
5```

# 题解

## 作者：lizhehao2009 (赞：6)

## 简要题意

给出 $t$ 组数据，每组数据当中有一个整数 $n$，以及一个长度为 $n$ 的整数序列，请问至少要从前往后删多少个元素，才能保证序列中剩下的元素互不相同？

## 分析

如果我们完全按照题意，每删掉一个数 $a_i$ 就访问第 $i+1$ 个元素到第 $n$ 个元素，看它门当中有没有相同的元素的话，时间复杂度就会是 $O(n^2)$，花费的时间过长。

但我们可以换一个角度来思考，从第 $n$ 个数开始，从后往前枚举，用一个桶来标记第 $a_i$ 个元素是否有出现过。如果发现第 $i$ 个元素在第 $i+1$ 到第个 $n$ 元素中已经出现过了，则证明删除前 $i$ 个元素能保证序列中剩下的元素互不相同，且删除元素的数量最少，输出 $i$，然后退出循环。如果序列中的每一个元素都互不相同，则在循环结束后输出 $0$。该算法的时间复杂度为 $O(n)$。

程序代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];//用来存储整数序列的数组
bool number[200010];//桶数组
int main()
{
    int t,n,flag;
    scanf("%d",&t);
    while (t--)
    {
        memset(number,0,sizeof(number));//初始化桶数组
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
        }
        flag=0;
        for (int i=n;i>=1;i--)
        {
            if (number[a[i]]==1)//判断这个元素是否有出现过
            {
                printf("%d\n",i);
                flag=1;//表示有需要删除的元素
                break;
            }
            number[a[i]]=1;//标记一下这个元素已经出现过
        }
        if (flag==0)//如果没有需要删除的元素
        {
            printf("0\n");//则输出0
        }
    }
    return 0;
}
```

---

## 作者：Awsdkl (赞：6)

# 分析
要让我们删去左边重复的数，我们可以理解为从右往左扫，扫到第一个重复的，则在它之前的和它都要删去  
因为从左往右扫，所以我用了栈（我也不知道我当时怎么想的）  
## 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
int n;
stack<int> a;
bool ab[200005]; //存储前面是否出现过
int thisint;
int ans;

int main()
{
	scanf("%d",&t);
	for(int i = 1;i <= t;i++)
	{
		scanf("%d",&n);
		ans = 0;
		for(int j = 1;j <= n;j++) //输入
		{
			scanf("%d",&thisint);
			a.push(thisint);
		}
		
		for(int j = 1;j <= n;j++) //从后往前判断第一个重复的
		{
			int num = a.top();
			if(ab[num]) break;
			else ab[num] = true;
			ans++;
			a.pop();
		}
		printf("%d\n",n - ans); //输出
		
		memset(ab,false,sizeof(ab)); //清空数组
		while(!a.empty()) a.pop();  //清空栈
	}
	return 0;
}
```
求过

---

## 作者：linyihdfj (赞：5)

## B.Remove Prefix

### 题目描述：
[原题面](https://codeforc.es/contest/1714/problem/B)

### 题目分析：

我们要使得某一个后缀不含有重复元素，也就是可以理解为我们将每个元素的倒数第二次出现的地方及之前删掉，这样所有的取最大值就是答案。

### 代码详解：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
int a[MAXN];
vector<int> v[MAXN]; 
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1; i<=n; i++){
			scanf("%d",&a[i]);
			v[a[i]].push_back(i);
		}
		int ans = 0;
		for(int i=1; i<=n; i++){
			if(v[i].size() > 1){
				ans = max(ans,v[i][v[i].size()-2]);
			}
		}
		printf("%d\n",ans);
		for(int i=1; i<=n; i++)	v[i].clear();
	}
	return 0;
}
```

---

## 作者：zhicheng (赞：3)

### 题意简述

有一个有 $n$ 个数的数组 $a$，求出一个最小的 $i$，使得 $a_i,a_{i+1},...,a_n$ 都互不相同。

### 思路

我们可以从后往前，记录一下 $a_i$ 是第几次出现。比如样例最后一组，原数组为 $[1,2,1,7,1,2,1]$，记录后的数组就是 $[4,2,3,1,2,1,1]$。这时要求所有数都不同，也就是说一个数最多出现一次，就找记录后的数组最长且连续的 $1$ 的后缀就可以了。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int p[200010],q[200010],w[200010];
int main(){
	int n,a,ans;
	scanf("%d",&n);
	while(n--){
		ans=0;
		memset(w,0,sizeof(w));  //记得清空
		scanf("%d",&a);
		for(int i=1;i<=a;i++){
			scanf("%d",&p[i]);
		}
		for(int i=a;i>=1;i--){
			q[i]=++w[p[i]];  //从后往前记录出现次数
		}
		for(int i=1;i<=a;i++){
			if(q[i]>1){
				ans=i;  //找到最后一个大于1的数，它及它前面的所有数都需要删去。
			}
		}
		printf("%d\n",ans);  //如果所有数都只出现了一遍，那么就要输出0，ans初始化为0即可
	}
}
```

---

## 作者：Qerucy (赞：2)

对于这道题，我们可以从后往前枚举每一个元素，看看它是否出现过，如果没有，就把这个元素保留，如果有，就删除这个元素及这个元素之前的所有元素，最后输出删除的元素数量即可。

代码：

```cpp
#include<bits/stdc++.h>
 
int b,c,t;
int n,h,m;
int a[1000010];
bool vis[1000010];
 
int main(){
    scanf("%d",&t);
    while(t--){
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        int now=n;//now用来存储从后往前数最后一个未重复的数的下标。
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        for(int i=n;i>=1;i--){
            if(vis[a[i]]) break;//如果该元素之前出现过就跳出循环。
            vis[a[i]]=1;//标记。
            now=i;//更新答案。
        }
        printf("%d\n",now-1);
        //因为now是从后往前数最后一个未重复的数的下标，所以我们需要删除now之前的数，也就是从1到now-1的数都要被删除。
    }
    return 0;
}

```


---

## 作者：Dregen_Yor (赞：2)

# 题目分析：

这题并不难，我们要使得某一个后缀不含有重复元素，我们记录每一个元素出现的位置和它上一次出现的位置，取上一次出现的位置的最大值，读入的时候处理即可，记录的最大值即为答案。

时间复杂度为 $O(n)$。

# 代码
```cpp
#include <bits/stdc++.h>
#define N 200010
using namespace std;

struct node {
	int la, now;
} book[N];
int t, n, maxn;

int main() {
	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		memset(book, 0, sizeof(book));
		maxn = 0;

		for (int i = 1; i <= n; i++) {

			int a;
			scanf("%d", &a);
			book[a].la = book[a].now;
			book[a].now = i;
			maxn = max(maxn, book[a].la);
		}

		printf("%d\n", maxn);
	}

	return 0;
}

```


---

## 作者：minVan (赞：2)

**题目大意**

给你 $n$ 个数字，每次可以去掉最左边的数字，最后要使得所有数字都是不同的，问最少要去掉多少个数字。

**解题思路**

用一个映射来存储元素是否出现过，若出现过则直接输出此时所处下标并且跳出循环，不过要注意要倒序循环，若正序循环则会超时。最后还要特判一下若所有元素都出现过直接输出 $0$。

**TLE 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
/*
双重循环，总时间复杂度约为 O(t * n * n)，超时。
正序。
*/
const int N = 2e5 + 5;
int a[N];
int main() {
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for(int len = n; len >= 1; len--) { // 长度
			bool flag = 0;
			map<int, int> mp;
			for(int i = n; i >= n - len + 1; i--) {
				if(mp[a[i]] == 1) { //若重复了
					flag = 1;
					break;
				}
				mp[a[i]] = 1; // 标记已有
			}
			if(!flag) {
				cout << n - len << "\n";
				break;
			}
		}
	}
	return 0;
}
```

**AC 代码，请勿抄袭**

```cpp
#include <bits/stdc++.h>
using namespace std;
/*
一重循环，总时间复杂度约为 O(t * n)，不会超时。
倒序。
*/
int t, n, a[200005];
map<int, int> mp;
int main () {
	cin >> t;
	while (t--) {
		mp.clear(); //每次清零
		bool flag = 0; //是否需要去除
		cin >> n;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for(int i = n; i >= 1; i--) { //倒序循环
			if(mp[a[i]]) { //若重复了
				cout << i << "\n";
				flag = 1;
				break; //跳出循环		
			}
			mp[a[i]] = 1; //标记已有
		}
		if(!flag) { //不需要去除
			cout << "0\n";
		}
	}
	return 0;
}
```

---

## 作者：tian_jun_cheng (赞：2)

## 思路

首先，我们记录每个数出现了几次。

```cpp
for(int i=1;i<=n;i++)
{
    cin>>a[i];
    m[a[i]]++;
}
```
同时，将每一个出现了 $ 2 $ 次即以上的数记录下来。

```cpp
for(int i=1;i<=n;i++)
    if(m[a[i]]>=2)
        s.insert(a[i]);
```
因为我们每次只能从左边删除，所以从左边开始寻找每一个数。如果这个数出现的次数为 $ 1 $ ，就将这个数删除。否则将这个数出现次数减 $ 1 $ 。

```cpp
for(int i=1;i<=n;i++)
    if(s.size()!=0)
    {
        cnt++;
        m[a[i]]--;
        if(m[a[i]]==1)	
            s.erase(a[i]);
    }
```

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		map <int,int> m;
		set <int> s;
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			m[a[i]]++;
		}
		for(int i=1;i<=n;i++)
			if(m[a[i]]>=2)
				s.insert(a[i]);
		for(int i=1;i<=n;i++)
			if(s.size()!=0)
			{
				cnt++;
				m[a[i]]--;
				if(m[a[i]]==1)	
					s.erase(a[i]);
			}
		cout<<cnt<<endl;
	}
	return 0;
}
```


---

## 作者：Jasper08 (赞：2)

本题可以用贪心的做法。从后往前扫描数组 $a$，由于题目保证了 $1\le a_i\le n$ 且 $n\le 2\cdot10^5$，所以我们可以开一个桶来判断每个数是否出现多次。定义 $sec_i$ 表示数 $i$ 倒数第二次在数组 $a$ 中出现的下标（如果只出现 $1$ 次或 $0$ 次则 $sec_i=0$） ，那么答案即为 $ans=\max(sec_1,sec_2,\cdots,sec_n)$。

举个例子模拟一下，当 $a=[1,3,2,3,1,4,5]$ 时，$sec_1=1,sec_2=0,sec_3=2,sec_4=0,sec_5=0$。所以要去除的数的数量即为 $\max(1,0,2,0,0)=2$。

贪心的感性证明：由于 $sec_i$ 表示的是 $i$ 倒数第二次在数组 $a$ 中出现的下标，所以在区间 $(sec_i,n]$ 中 $i$ 只会出现一次。而在区间 $(ans,n]$ 中，所有数都只会出现 $0$ 次或 $1$ 次，满足题目的要求。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e5+10;

int t;
int a[N], sec[N];  
bool check[N]; //check数组判断每个数是否有被计算过

int main() {
	scanf("%d", &t);
	while (t -- ) {
		int n;
		scanf("%d", &n);
		memset(a, 0, sizeof a);
		memset(sec, 0, sizeof sec);
		memset(check, 0, sizeof check); //多测注意清空
		
		int ans = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for (int i = n; i >= 1; --i) { //计算sec[1~n]
			int x = a[i];
			if (check[x] == 0) check[x] = 1; //如果第1次出现,则check[x]=1
			else sec[x] = max(sec[x], i); //如果出现多次,则取下标最大值
		}
		for (int i = 1; i <= n; ++i) ans = max(ans, sec[i]);
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：mzyc_yang2021 (赞：1)

题意：给一堆序列，问从前往后移除多少个数字后才能使这个序列里面的数字不重复。

思路：用集合来装序列，因为集合可以排序去重。遇到没有重复的数字，加入集合，否则直接退出循环。

注意：题目说从前往后连续删，则会出现一种情况：若当前数字是第一次出现，而后面还有重复的数字，那删去的数字就不是连续的。这样我们就倒着读入，若出现重复数字，直接退出循环。

代码（加解释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200010
set<int>s;
int t,n,a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1,x;i<=n;i++) cin>>a[i];
		for(int i=n;i>=1;i--) // 倒序加入集合 
		{
			if(s.count(a[i])==0) s.insert(a[i]); // 若没出现，就加入 
			else break; // 否则退出循环 
		}
		cout<<n-s.size()<<"\n"; // 那么答案就是数字总数减去集合中元素个数 
		s.clear(); // 记得清空集合 
	}
	return 0;
}
```


---

## 作者：Jeremiahy (赞：1)

## 题意

给定长度为 $n$ 的序列 $a$（$1\le a_i\le n$），每次可以去除最前面的一个数字，多少次去除可以使得 $a$ 中元素互不相同？

# 分析

正难则反。如果正着找的话，每次暴力统计花费时间太高，那么我们可以倒着找，用 $v$ 数组标记每个数是否出现过，第一次遇见一个重复的数字就可以直接计算出要去除的次数了。

设第 $i$ 位数字与后面的有重复，那么答案就是 $i$（第 $i$ 位也要去除）。

另外，如果不需要去除的话，输出 $0$。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200005], num[200005];
signed main () {
	cin >> t;
	while (t--) {
		memset(num, 0, sizeof(num));//每次清零
		bool flag = 0;//是否需要去除
		cin >> n;
		for (register int i = 1; i <= n; i++)
			cin >> a[i];
		for (register int i = n; i >= 1; i--) {//倒序循环
			if (num[a[i]]) {//重复
				cout << i << '\n', flag = 1;
				break;				
			}
			num[a[i]] = 1;//标记已有
		}
		if (!flag)//不需要去除
			cout << 0 << '\n';
	}
	return 0;
}
```


---

## 作者：032o35 (赞：1)

题意：给定一个序列，求一个最小的非负整数 $n$，使得此序列删除前 $n$ 个数后，剩下的数都不重复。

思路：题意可转换为：求序列后端**最多**有多少个数不重复，所以可以先读入序列，然后作**倒序处理**：读入一个数 $x$，若此数在之前没有出现过，修改标志数组；否则输出当前的位置 $i$。如果遍历完后依然没有输出，输出 $0$。

时间复杂度分析：因为每个数最多判断一次，时间复杂度为 $O(n)$。

核心代码部分：
```cpp
	int fl=0;
	for(int i=n;i;i--){//倒序处理
		if(f[a[i]]){cout<<i<<"\n";fl=1;break;}//不符合要求，改标志，输出
		f[a[i]]=1;//改标志数组
	}
	if(!fl)cout<<"0\n";//没有输出，输出0
```
谢谢资瓷！

---

## 作者：cachejtt (赞：1)

## 题意
给你一个序列，从前端删除 $x$ 个数，使得剩余序列中每个数字仅出现一次。问 $x$ 最小值。

## 思路
正难则反，从后往前搜，如果当前这个数已经出现过，那么立即停止并输出。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define endl "\n"
#define int ll
using namespace std;
int t,n,m,k;
int ans,sum;
int a[200005],vis[200005];
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    int flag=0;
    memset(vis,0,sizeof(vis));
    rep(i,1,n){
      cin>>a[i];
    }
    nrep(i,n,1){
      if(vis[a[i]]==1){
        cout<<i<<endl;
        flag=1;
        break;
      }
      else vis[a[i]]=1;
    }
   if(flag==0)cout<<0<<endl; 
  }
  return 0;
}

```

---

## 作者：TheCliffSwallow (赞：1)

### 题意简述
给定 $t$ 组测试数据，每次给一个长度为 $n$ 的序列，让你从前往后删数字，求删多少个才能让这个序列没有重复的数字。
### 思路
我们从后往前判断，因为 $1\le a_i \le n \le 200000$，所以可以用一个桶判断重复数字，如果判断到重复数字就直接跳出循环，输出的就是当前循环变量。
### AC Code
```cpp
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cstring>
#include<string>
#include<cctype>
#define ll long long
#define ull unsigned long long
using namespace std;
int i,j,t,n,a[200005];//其实a不用数组也行
bool busket[200005];
int main(){
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>n;
		memset(busket,false,sizeof(busket));//注意要清零
		for(i=1;i<=n;i++)	cin>>a[i];
		for(i=n;i>=1;i--){
			if(busket[a[i]]){
				break;//重复了就直接跳出循环
			}
			busket[a[i]]=true;
		}		
		cout<<i<<endl;
	}
  	return 0;
}
```


---

## 作者：Yizhixiaoyun (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1714B)

## 题目翻译

给定长度为 $n$ 的序列，每一次操作可以去除最前面的一个数字，请问经过多少次操作可以使得该序列中所有元素各不相同？

## 题目分析

遇到这道题，我们第一反应就是暴力从前往后找。但是这样明显会超时，那么我们采用另一种思路。

我们发现，既然要没有重复元素，那我们就可以将每个数除了最后一次之外出现的地方全部删掉，删完之后扫一遍，寻找最大值即可。

## 贴上代码

附：本题似乎卡了 ```cin``` 和 ```cout``` ，建议使用格式化输入输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int T;
int n,a[maxn];
int ans;
vector<int> vc[maxn]; 
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);ans=0;for(register int i=1;i<=n;++i) vc[i].clear();
		for(register int i=1;i<=n;++i){
			cin>>a[i];vc[a[i]].push_back(i);
		}
		for(register int i=1;i<=n;++i){
			if(vc[i].size()>1) ans=max(ans,vc[i][vc[i].size()-2]);
		}
//		cout<<ans<<endl;
		printf("%d\n",ans);
	}
}
```

---

## 作者：xzy090626 (赞：0)

# CF1714B 题解
## 题意
给定一个长为 $n$ 的序列 $a$（$1\le a_i\le n$），每次操作可以去除最前面的一个数字。你需要输出，最少多少次操作之后， $a$ 中元素互不相同？

多测，$1\le n\le2\cdot10^5$，$1\le t\le 10^4$。
## 分析
赛时用了个很笨的方法，还吃了一发罚时，警钟长鸣。

看了其他的题解，大多都是从后往前倒着扫一遍。

但是我赛时思路清奇，想到从前往后扫，每次记录当前每个值出现的次数。

记录完每个数出现的次数之后，我们再次遍历。

我们用一个变量 $cnt$ 来记录目前总共出现的不同的数值的数量。

每扫完一个 $a_i$ 之后，将 $a_i$ 出现的次数减 $1$。如果此时它出现的次数 $\le 1$，那么 $cnt$ 减 $1$。

当此时的 $i$ 与 $cnt$ 的和为 $n$ 时，意味着每个数都只出现了一次，我们可以直接输出 $i$。

入如果循环到了结尾，那么输出 $n-1$ 即可。

如何记录每个数出现的次数？可以用 map；由于原题数据较小，直接开数组也行。时间复杂度分别为 $O(n \log n)$  和 $O(n)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 7;
int s[N];
void solve(){
	int n;
	cin>>n;
	map<int,int>a;
	int cnt = 0;
	for(int i=0;i<n;++i){
		cin>>s[i];
		if(!a[s[i]]) cnt++;
		a[s[i]]++;
	}
	for(int i=0;i<n;++i){
		if(n-i==cnt){
			cout<<i<<'\n';
			return ;
		}
		if(a[s[i]]==1) cnt--;
		a[s[i]]--;
	}
	cout<<n-1<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
// /oh/hsh
```

---

## 作者：sixrc (赞：0)

由于你只能从开头开始删，所以本质就是让你求一个最小的 $p$，使得 $a_{[p,n]}$ 数字互不相同。

很显然我们从后往前扫，判断一个数是否出现。如果我们当前扫到的这个数已经出现过了，且是第一个出现两次的数，那就停止循环，输出从这个数到开头的长度即可。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200010], p[200010];
int main(){
	scanf ("%d", &t);
	while (t --){
		scanf ("%d", &n);
		for (int i=1; i<=n; i++){
			scanf ("%d", &a[i]);
			p[i] = 0;
		}
		int s = 0;
		p[0] = 1;
		for (int i=n; i>=0; i--){
			if (p[a[i]]){
				s = i;
				break;
			}
			p[a[i]] = 1;
		}
		cout << s << endl;
	}
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1Qg41117Qb)

### 2 思路

如果第 $i$ 个数字在第 $i+1$ 到 $n$ 个数字中也出现过，说明必须要从 $1$ 删掉 $i$。

我们可以从后往前简单模拟一下，更新每个数字出现次数，发现重复数字及时记录答案即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
int t;
int n;
int a[max_n+2];
int cnt[max_n+2];
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1714B_1.in","r",stdin);
	freopen("CF1714B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
			cnt[i]=0;
		}
		ans=0;
		for(int i=n;i>=1;--i){
			++cnt[a[i]];
			if(cnt[a[i]]>=2){
				ans=i;
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/82203947)

By **dengziyue**

---

## 作者：zfx_VeXl6 (赞：0)

## 我的翻译
### 题目描述

$t$ 组数据（$1\le t\le10^4$）。

每组数据，给定 $n$（$1\le n\le2\cdot10^5$）和序列 $a=[a_1,a_2,\dots,a_n]$（$1\le a_i\le n$），需要删除$a$的一个前缀，使剩下的数不重复。

找出要删除的最小前缀，输出它的长度。

### 样例解释

删除最小前缀后，剩下的序列分别是：

* $[1,4,3]$
  
* $[1]$
  
* $[1]$
  
* $[6,5,4,3,2,1]$
  
* $[2,1]$
  

所有剩下的序列只包含不同的元素。

---

## 解法
对于每个序列，只需要找出从后往前第一个与之后的数字重复的数字的下标即可。不存在这个数字输出 $0$。

考虑使用STL中的set容器，从后往前遍历每个序列元素，若不在set中则加入set，若已经存在，下标就是答案。可设置一个虚拟元素 $a_0=a_1$ ，遍历从 $n$ 到 $0$ ，若 $[a_1,a_2,\dots,a_n]$ 中无重复数字， $0$ 就是答案。

核心代码：
```cpp
int t,n,a[200001];
set<int>st;

scanf("%d",&t);
while(t--)
{
	scanf("%d",&n);
	st.clear();					//使用前清空容器
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	a[0]=a[1];					//虚拟元素
	for(int i=n;i>=0;i--)		//遍历
		if(st.count(a[i]))		//判断当前元素是否与已进入容器的元素重复
		{
			cout<<i<<'\n';		//重复，下标即为答案
			break;
		}
		else
			st.insert(a[i]);	//不重复，加入容器
}
```

---

## 作者：YCSluogu (赞：0)

## CF1714B 题解

### 题目大意

一共 $t$ 组数据，每组数据给定一个数字 $n$ 与包含 $n$ 个整数的数组。你每次操作可以删除数组第一个元素，求至少操作多少次后整个数组没有重复元素。

### 思路

由于题目要求我们一定只能删除第一个元素，不妨我们倒序遍历每一个元素。因为越靠后的元素越会被晚删除。所以，对于每一个元素我们只需要保存它最后一次在数组出现的位置就好。

于是我们倒序遍历时，若出现一个元素在之前遍历途中出现过，说明此元素必须被删除，此时我们直接输出这个元素的下标就好。

### 代码

``` cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e6;

int  t;
int  n;
int  a[kMaxN];
bool same[kMaxN];

void solve() {
  memset(same, false, sizeof(same));
  cin >> n;
  for (int i = 1; i <= n; i++) { cin >> a[i]; }
  for (int i = n; i >= 1; i--) {
    if (same[a[i]]) {
      cout << i << endl;
      return;
    }
    same[a[i]] = true;
  }
  cout << 0 << endl;
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) { solve(); }
  return (0 - 0);
}
```


---

