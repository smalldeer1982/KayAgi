# Restoring Permutation

## 题目描述

You are given a sequence $ b_1, b_2, \ldots, b_n $ . Find the lexicographically minimal permutation $ a_1, a_2, \ldots, a_{2n} $ such that $ b_i = \min(a_{2i-1}, a_{2i}) $ , or determine that it is impossible.

## 样例 #1

### 输入

```
5
1
1
2
4 1
3
4 1 3
4
2 3 4 5
5
1 5 7 2 8```

### 输出

```
1 2 
-1
4 5 1 2 3 6 
-1
1 3 5 6 7 9 2 4 8 10```

# 题解

## 作者：_6_awa (赞：7)

题目：有一个长度为 $n$ 的序列 $b_1,b_2,...,b_n$，求字典序最小的序列$a_1,a_2,...a_{2n}$，使得 $b_i=\min(a_{2i-1},a_{2i})$，若无解，输出数字 $-1$。

思路：贪心+模拟

我们发现：因为要满足字典序最小，所以要把 $b_i$ 放在 $a_{2i-1}$ 位。剩下的就从 $b_i$ 开始找，如果没被占用，则直接取它使字典序最小。如果没有一个满足条件，输出 $-1$。

附代码：

```
#include <iostream>
#include <cstring>
using namespace std;
int t,n,a[499],x,b[499];
int main()
{
    cin >> t;
    while(t --)
    {
        memset(b,0,sizeof(b));
        int p = 0;
        cin >> n;
        for(int i = 1;i <= n;i ++)cin >> x,a[2 * i - 1] = x,b[x] = 1;//标记+放位
        for(int i = 2;i <= 2 * n;i += 2)
        {
            int r = 0;
            for(int j = a[i - 1];j <= 2 * n;j ++)
                if(b[j] == 0)//找到了
                {
                    b[j] = 1,r = 1,a[i] = j;//取最小值，标记
                    break ;
                }
            if(r == 0)//没找到输出-1
            {
                cout << "-1\n";p = 1;
                break ;
            }
        }
        if(p)continue;
        for(int i = 1;i <= 2 * n;i ++)cout << a[i] << " ";//否则直接输出
        cout << "\n";
    }
}
```



---

## 作者：Kle1N (赞：1)

警示后人：这题翻译有锅，不是**序列** **$a$**，而是**排列** $a$。

---
首先，因为题目要求字典序最小，所以我们贪心地想，肯定要把 $b_i$ 放到 $a_{2i-1}$ 上。证明也很简单，假设把 $b_i$ 放到 $a_{2i}$ 上最优，则因为 $a$ 是一个排列，$a_{2i-1} \neq a_{2i}$，所以 $a_{2i-1} > a_{2i}$。那么此时交换 $a_{2i-1}$ 和 $a_{2i}$，得到的新序列字典序更小，与原命题矛盾，所以原命题不成立。

于是我们求出了所有的 $a_{2i-1}$。

接下来，因为 $a$ 是一个 $1$ 到 $2n$ 的排列，所以必须保证序列中 $1$ 到 $2n$ 的每一个数都恰好只出现一次。于是我们可以开一个标记数组，出现过的数都打上标记。然后我们采用枚举来求 $a_{2i}$，范围显然就是 $a_{2i-1}+1$ 到 $2n$。如果一个数没被标记过，那就标记它并记录答案，否则继续枚举。要是发现 $a_{2i-1}+1$ 到 $2n$ 所有数都被标记过，说明无解，输出 $-1$ 即可。

这里有个问题，为什么枚举过程中不用考虑字典序的问题呢？

因为我们是从前往后、从小到大遍历的，所以只要能够找到解，就能保证字典序一定最小。

---
具体看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,b[105],a[205];
bool f[205],t;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		memset(f,0,sizeof(f));
		t=0;
		for(int i=1;i<=n;i++){
			cin>>b[i];
			f[b[i]]=1;
		}
		for(int i=1;i<=n<<1;i++){
			if(i&1){
				a[i]=b[(i+1)>>1];
			}
			else{
				t=1;
				for(int j=b[i>>1]+1;j<=n<<1;j++){
					if(!f[j]){
						f[j]=1;
						t=0;
						a[i]=j;
						break;
					}
				}
				if(t){
					break;
				}
			}
		}
		if(t){
			cout<<-1<<"\n";
		}
		else{
			for(int i=1;i<=n<<1;i++){
				cout<<a[i]<<" ";
			}
			cout<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：TLMPEX (赞：1)

这是一道稍微复杂的模拟题，思路详见代码。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int k[101],a[201],vis[201];
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis));//初始化
		int n,i,j,t=1,cnt=0;//cnt表示a数组当前有多少个数,t表示有没有输出过
		cin>>n;
		for(i=1;i<=n;i++){
			cin>>k[i];
			vis[k[i]]=1;//标记k[i]，表示用过k[i]了
		}
		for(i=1;i<=n;i++){
			a[++cnt]=k[i];//用k[i]这个数
			int f=1;//表示没有可以用的数
			for(j=a[cnt]+1;j<=2*n;j++)
				if(!vis[j]){//如果这个数没用过
					a[++cnt]=j;//用这个数
					f=0;//有可以用的数
					vis[j]=1;//标记j这个数
					break;
				}
			if(f){//如果没有可以用的数，输出“-1”
				t=0;//表示输出过了
				cout<<"-1"<<endl;
				break;
			}
		}
		if(t){//如果灭输出，则输出a数组
			for(i=1;i<=cnt;i++)
				cout<<a[i]<<" ";
			cout<<endl;
		}
	}
}
```


---

## 作者：流绪 (赞：1)

数据很小，暴力写即可。

题意，给一个序列bi，让你根据这个序列构造一个新序列ai，使新序列满足 bi=min(a2i-1 - a2i)。bi 有 n 项，故 ai 有 2n 项且题目要求 ai 中 1 到 2n 所有数字均要出现。

我们输入时记录每个数是否出现，然后遍历每个 bi，在它后面加上一个比他大且还未用过的最小数的数，这个大的数直接从 bi 到 2n 里暴力找就行啦，如果大于 2n 还没找到，那就说明这个序列不能合法的构造出来输出 -1。遍历完每个 bi 输出结果接好啦。

为什么用比 bi 大且未用过的最小数呢？对于每一个 bi，它后面放的那一个数一定是大于它的，如果选用比 bi 大且未用过的最小数，那么序列 b 后面其他项的选择空间就会更大。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
using namespace std;
int a[maxn];
int b[maxn];
int v[maxn] = {0};
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		memset(v,0,sizeof(v));//初始化
		for(int i=1;i<=n;i++)
		{
			cin >> a[i];
			v[a[i]] = 1;//记录是否出现
		}
		int p=1,flag = 1;//计数器与能否构造的标志
		for(int i=1;i<=n;i++)
		{
			b[p++] = a[i];//把bi加入答案数组
			while(1)//找比bi大的数
			{
				a[i]++;
				if(!v[a[i]]&&a[i]<=2*n)
				{//未出现且值合法
					v[a[i]] = 1;//标记为出现
					b[p++] = a[i];加入答案数组
					break;
				}
				else if(a[i] > 2*n)
				{//值不合法
					flag = 0;
					break;
				}
			}
		}
		if(!flag)
			cout << -1;
		else
			for(int i=1;i<p;i++)
				cout << b[i] << " ";
 		cout << endl;
	}
	return 0;
}
```


---

## 作者：pyz51 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1315C)
# 题意简述
~~题面已经够简单了~~  
给定长度为 $n$ 的序列 $b$，求长度为 $2n$ 的排列 $a$，  
满足： 
$$\forall b_x=\min \{ a_{2x-1},a_{2x} \}$$
$$\forall a_x \in [1,2n]$$
$$\forall a_x,a_y~~a_x\not=a_y$$
且**字典序最小**。
# 题解
首先可以想到 $a_{2x-1}$ 应等于 $b_x$。  
因为 $a_{2x-1}$ 在 $a_{2x}$ 前，字典序最小意味着靠前的小比靠后的小更重要，而根据条件，在 $a_{2x-1}$ 和 $a_{2x}$ 之中，最小的数值是 $b_x$，所以 $a_{2x-1} = b_x$。

想完了 $a_{2x-1}$，该想想 $a_{2x}$ 了。
由于 $a$ 的字典序应尽量小，所以 $a_{2x}$ 是除掉所有 $b_i$ 和已经选过的数的最小的正整数，又因 $a_i\in[1,2n]$，所以要判断这个最小值是否超过 $2n$，超过就输出 $-1$。
# AC Code
```cpp
#include<iostream>
#include<string.h>
using namespace std;
int t,n,a[105],b[205],c[105];
int main(){
    cin>>t;
    while(t--){
        bool f=0;
        memset(b,0,sizeof b);
        memset(c,0,sizeof c);
        //初始化
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i],b[a[i]]=1;
        for(int i=1;i<=n;i++){
            for(int j=a[i]+1;j<=2*n;j++){
                if(!b[j]){//如果这个数没被选过
                    c[i]=j;//让a[2i]=j
                    b[j]=1;
                    break;
                }
            }
        }
        for(int i=1;i<=n;i++){
            if(!c[i]){//如果有数不满足条件没计入，输出-1
                cout<<"-1\n";
                f=1;
                break;
            }
        }
        if(!f){
            for(int i=1;i<=n;i++) cout<<a[i]<<' '<<c[i]<<' ';
            cout<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：DengDuck (赞：0)

其实时间复杂度可以 $\mathcal O(n\log n)$ 的。

还是和大部分题解一样的思路，首先 $b_{2i-1}=a_i$，这是肯定的，因为 $b_{2i-1}$ 和 $b_{2i}$ 必然有一个是 $a_i$，而 $a_i$ 字典序会小一点。

然后考虑求 $b_{2i}$，显然我们可以贪心地安排剩余数字中的 $a_i$ 的后继，这样字典序最小，如果找不到后继，就无解，用 STL 科技维护比较快，找后继，删数字可以做到 $\mathcal O(\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e6+5;
LL T,n,a[N],b[N];
set<LL>s;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		s.clear();
		for(int i=1;i<=2*n;i++)
		{
			s.insert(i);
		}
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			s.erase(a[i]);
			b[2*i-1]=a[i];
		}
		LL flg=0;
		for(int i=1;i<=n;i++)
		{
			auto t=s.upper_bound(a[i]);
			if(t==s.end())
			{
				flg=1;
				break;
			}
			b[2*i]=*t;
			s.erase(t);
		}
		if(flg)
		{
			puts("-1");
			continue;
		}
		for(int i=1;i<=2*n;i++)
		{
			cout<<b[i]<<' ';
		}
		cout<<endl;
	}
}
```

---

## 作者：lcc17 (赞：0)

### **Solution:**

贪心即可，用used数组记忆一个数是否被用过。

由于a[i]和a[i+1]的顺序不影响答案，所以不妨设a[i]和a[i+1]中的较小数为a[i]。

显然为了在后面不冲突，a[i+1]要选择只比a[i]大一点且未被选过的数，如果没有这样的数，说明构造不出a数组，输出-1

具体见代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
inline int read(){
	int f=1,res=0;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=res*10+c-'0',c=getchar();}
	return f*res;
}
int t,n,b[1001],a[1001];
bool used[1001],f;
void init(){
	n=read();
	memset(used,0,sizeof(used));
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));//初始化 
	for(int i=1;i<=n;i++){
		b[i]=read();
		used[b[i]]=1;//b[i]已经被用了 
	}
	int cnt=0;//cnt记录a数组现在要选什么 
	for(int i=1;i<=n;i++){
		a[++cnt]=b[i];//因为b[i]为a[cnt],a[cnt+1]中的较小数，又设a[cnt]<[cnt+1] 
		f=0;//是否存在数可以成为a[cnt+1] 
		for(int j=a[cnt]+1;j<=2*n;j++)
			if(!used[j]) {
				a[++cnt]=j,used[j]=1,f=1;break;//记录 
			}
		if(f==0){//没有数可以 
			puts("-1");
			return ;
		} 
	}
	for(int i=1;i<=cnt;i++) printf("%d ",a[i]); 
	printf("\n");
	return ;
}
int main(){
	t=read();
	while(t--) init(); 
	return 0;
} 
```


---

