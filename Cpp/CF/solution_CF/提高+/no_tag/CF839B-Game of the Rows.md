# Game of the Rows

## 题目描述

现在有 $K$ 个队，飞机有 $N$ 排座位，每排能坐 $8$ 个人，不同队伍的人不能坐相邻的位置。

相邻情况有 $5$ 种 $(1, 2), (3, 4), (4, 5), (5, 6), (7, 8)$。请问这 $n$ 排座位是否够坐。

（$K$ 个队的总人数小于 $8 \cdot N$）

## 样例 #1

### 输入

```
2 2
5 8
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1 2
7 1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1 2
4 4
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
1 4
2 2 1 2
```

### 输出

```
YES
```

# 题解

## 作者：WCG2025 (赞：3)

根本不用其他人做的那么麻烦，就是确定一个策略就好了

肯定是先将四人座用完，因为四人座用不完的话就只能用来当双人座甚至是单人座，这肯定是不划算的

只要有两个人就分双人座，尽量少分单人出来

最后判断就是看单人座够不够，够的话就输YES，不够NO就完了

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char ch=getchar();
    int x=0,f=1;
    while(ch<'0'||ch>'9')
    {
       if(ch=='-') f=-1;
       ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
       x=x*10+ch-'0';
       ch=getchar();
    }
    return x*f;
}
int n,k;
int a[105];
int main()
{
    	n=read();
    	k=read();
        for(int i=1;i<=k;i++)
            a[i]=read();
        int ans1=n;//四人座只有n个
        int ans2=2*n;//双人座2*n个
        for(int i=1;i<=k;i++)
		{
            int d=min(ans1,a[i]/4);//判断当前四人座最多装多少人
            ans1-=d;
            a[i]-=d*4;
        }
        ans2+=ans1;//多余的四人座先用于双人座
        for(int i=1;i<=k;i++)
		{
            int d=min(ans2,a[i]/2);//同上
            ans2-=d;
            a[i]-=d*2;
        }
        int tmp=ans2+ans1;//四人座和二人座都可以用于单人
        for(int i=1;i<=k;i++)
            tmp-=a[i];
        if(tmp>=0)
        	printf("YES\n");
        else
            printf("NO\n");
}
```

---

## 作者：Moon_Wind (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF839B)

**本题坑点**

要注意，四排的座位可以坐两个不同队伍的 $3$ 个人（我就是在这被卡了半个小时）。

众所周知，当 $4$ 人座能够坐满时，就尽量坐四人座，然后再把没有被坐的 $4$ 人座和 $2$ 人座坐上 $2$ 个人。最后再把只坐了两个人的 $4$ 人座和没有人坐的 $2$ 人座安排上一个人，如果还没有坐下所有人，则这  $n$ 排座位不够坐。
```cpp
#include<bits/stdc++.h>
#define int long long//建议开long long
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0); 
	int n,a[101],k,sum,sun;
	cin>>k>>n;
	for(int i=0;i<n;i++) cin>>a[i];
	sum=k;//四人座只有n个
	sun=k*2;//双人座有2*n个
	for(int i=0;i<n;i++){
	int y=min(sum,a[i]/4);
		sum-=y;//剩余四人座数量减去本轮用去的
		a[i]-=y*4;//这一队人数减去本轮坐下的
	}
	sun+=sum;//二人座数量加上剩余四人座数量
	for(int i=0;i<n;i++){
		int y=min(sun,a[i]/2);
		sun-=y;//剩余二人座数量减去本轮用去的
		a[i]-=y*2;//这一队人数减去本轮坐下的
	}
	sun+=sum;//一人座数量
	for(int i=0;i<n;i++) sun-=a[i];//一人座数量减去尚未安排的人数
	if(sun>=0) cout<<"YES";
	else cout<<"NO";
	return 0;
} 
```

本人只是一名蒟蒻，若有错误请多多包涵，谢谢大家。

---

## 作者：牙神幻十郎 (赞：1)

洛谷上remote judge第一个AC。嘿嘿

其实这题就是贪心，但是有点坑，因为**有一些细节**。

大体思路：对于每一排，我们安排座位时，找出能凑齐的，然后坐上去。关键一点是优先凑齐中间四人。所以写循环时，先把中间四个干死，再安排两个的。全部安排完了，每个座位还能单独做人。
### 但是！你以为这就完了？
中间四排其实还可以坐两个队三个人！

所以这题就是纯粹的模拟，但是一定要想清楚，不然会错很多点。
附上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n,k;
	cin>>n>>k;
	int a[k];
	for (int i = 0; i < k; ++i)
		cin>>a[i];
	bool f[n],t1[n],t2[n];
	memset(f,2,sizeof(f)),memset(t1,1,sizeof(t1)),memset(t2,1,sizeof(t2));
	for (int j = 0; j < n; ++j)
		for (int i = 0; i < k; ++i)
			if(a[i]>=4){
				a[i]-=4;f[j]=0;break;//以上，分配四座	
			}
	for (int j = 0; j < n; ++j)
		for (int i = 0; i < k; ++i)
			if(a[i]>=2&&f[j]){
				a[i]-=2;f[j]=1;break;//四座坐两队三人
			}
	for (int j = 0; j < n; ++j)
		for (int i = 0; i < k; ++i)
			if(a[i]>=2){
				a[i]-=2;t1[j]=0;break;//分配左边两座
			}
	for (int j = 0; j < n; ++j)
		for (int i = 0; i < k; ++i)
			if(a[i]>=2){
				a[i]-=2;t2[j]=0;break;//分配右边两座
			}
	int left=0,sum=0;
	for (int i = 0; i < n; ++i)
		left+=f[i]+t1[i]+t2[i];
	for (int i = 0; i < k; ++i)
		sum+=a[i];
	if(sum<=left)	cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF839B Game of the Rows
## 题目翻译
一架飞机有 $n$ 排，每排座位形如 $2,4,2$ 放置着 $8$ 个座位（逗号相当于过道）。现在有 $k$ 个旅行团，第 $i$ 个旅行团有 $a_i$ 个人，现在问能否全部坐下并满足不同旅行团的成员之间要么隔一个座位，要么隔一个过道。
## 小模拟 $+$ 贪心
由于过道把座位分割，所以每一组座位之间都是互不影响的，所以问题座位就变成了 $n$ 个四人座和 $2n$ 个双人座。\
因为我们总座位数是不变的，于是我们肯定希望座位的利用率越高越好。那利用率最高就是坐满，于是所有的旅行团，只要能坐满四人座就都坐四人座，能坐满二人座就坐二人座。\
我们进一步考虑如果所有四人坐满后的四人座该怎么办呢？\
首先由于没有 $\ge4$ 人的旅行团了，所以坐三人一定是性价比最高的方案，于是只要有旅行团剩 $3$ 人就让他们坐。\
接下来我们把是否有剩余 $4$ 人座当作标准分类讨论：
- 没有剩余。那么只剩下二人座了，这种情况对于剩余人数偶数的旅行团在之前已经分完了，就只剩下剩余 $1$ 人的旅行团了，这种情况之间判断剩余二人座数量是否大于剩余旅行团数量即可。
- 有剩余。这时候对于四人座，我们只剩下 $2+1$ 或 $2$ 或 $1+1$ 的选择了。由于要利用率尽可能高，于是我们就可以自然地想到多选择 $2+1$ 的方案。这里有个小细节，假设出现 $[2,2,2]$ 三个旅行团，我们是可以通过把中间的 $2$ 拆成 $1+1$ 的方法只需要 $2$ 个四人座就可以坐下。

这道题的细节还是不少的，但是只要思考清楚上面几点，代码也是手到擒来了。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,num2,num4,odd,even;
multiset<int>s;
signed main(){
    cin>>n>>k;
    num2=n<<1ll;
    num4=n;
    for(int i=1;i<=k;++i){
        int x;cin>>x;
        s.insert(x);
    }
    while(num4&&s.size()&&*s.rbegin()>=3){
        auto x=s.end();x--;
        int y=*x,z=y;
        s.erase(x);
        if(y==3){
            num4--;
            continue;
        }
        y/=4;
        if(y<=num4){
            num4-=y;
            z-=4*y;
        }else{
            z-=num4*4;
            num4=0;
        }
        if(z)s.insert(z);
    }
    if(s.empty()){
        cout<<"YES\n";
        return 0;
    }
    while(num2&&s.size()&&*s.rbegin()>=2){
        auto x=s.end();x--;
        int y=*x,z=y;
        s.erase(x);
        y/=2;
        if(y<=num2){
            num2-=y;
            z-=2*y;
        }else{
            z-=2*num2;
            num2=0;
        }
        if(z)s.insert(z);
    }
    if(s.empty()){
        cout<<"YES\n";
        return 0;
    }
    while(*s.rbegin()>=3){
        auto x=s.end();x--;
        s.erase(x);
        s.insert(*x-2);
        s.insert(2);
    }
    for(int i:s){
        if(i&1)odd++;
        else even++;
    }
    if(odd>=even){
        if(num4*2+num2>=s.size()){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
    }else{
        int d=min(odd,num4);
        num4-=d;
        int add=0;
        if(num4>=2){
            add=3*num4/2;
        }
        num4%=2;
        if(num4+num2+add>=s.size()){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
    }
    return 0;
}
```

---

## 作者：tanghg (赞：0)

## 思路
由于中间的两个椅子（看成四人座）占得人比较多，所以先把这个椅子坐满肯定很好，因为除了中间都不跟人触碰。我们把中间的全放上一个队。放到不能放为止。这样的四人座有 $n$ 个。

之后比较优秀的是二人座，因为可以容纳两名一个队的人。这样的座位原本有 $2\times n$ 个，但因为有可能四人座没做完，加上剩余的四人座个数即可。

最后把剩余的算成单人座即可。也就是剩余的前两个座位的个数个。
## 代码
```cpp
#include <iostream>
#include <cstdio>

using namespace std;
typedef long long ll;
const ll MAXN = 1e4 + 5;
ll n, k, a[MAXN];

int main() {
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= k; ++i) {
        scanf("%lld", &a[i]);
    }
    ll four = n;
    for (int i = 1; i <= k; ++i) {
        ll num = min(four, a[i] / 4);//有这么多的空位要做或者可以做
        four -= num;//四人座座位减掉这些
        a[i] -= num * 4;//每个座位可以做4个人，所以减掉座位数乘以4
    }
    //二人座同上
    ll two = 2 * n + four;
    for (int i = 1; i <= k; ++i) {
        ll num = min(two, a[i] / 2);
        two -= num;
        a[i] -= num * 2;
    }
    ll left = two + four;//剩余（单人座）
    for (int i = 1; i <= k; ++i) {
        left -= a[i];
        if (left < 0) {
            printf("NO\n");//座位数小于0了就不行了
            return 0;
        }
    }
    printf("YES\n");//否则可以
    return 0;
}
```

---

