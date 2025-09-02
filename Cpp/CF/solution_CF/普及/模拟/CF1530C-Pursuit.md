# Pursuit

## 题目描述

你和你的朋友伊利亚正在参加由多个阶段组成的编程竞赛。

对于每个阶段，你和伊利亚都会获得一个分数，保证为 $0$ 到 $100$ 之间的整数。并且，每个人获得的分数都是相互独立的，不受对方影响。

总分是这样计算的：设当前已进行 $k$ 个阶段，则你的总分为最高的 $k-\left\lfloor k\div4\right\rfloor $个阶段得分之和。其中 $\left\lfloor a\right\rfloor$ 代表 $a$ 向下取整（不大于 $a$ 的最大整数）。

现在，这个竞赛已进行了 $n$ 个阶段，你也知道这些阶段中，两个人获得的分数。但比赛仍在进行。请问：理论上，至少再过多少个阶段，你的总分才能超过伊利亚？如果你的总分已经超过了她，请输出 `0`。

## 样例 #1

### 输入

```
5
1
100
0
1
0
100
4
20 30 40 50
100 100 100 100
4
10 20 30 40
100 100 100 100
7
7 59 62 52 27 31 55
33 35 50 98 83 80 64```

### 输出

```
0
1
3
4
2```

# 题解

## 作者：Daidly (赞：2)

一道模拟题，有一些细节。

贪心策略：让 A 一直取 $100$，B 一直取 $0$。

由于进行的场数是变化的，设当前进行场数为 $n$，最多再进行 $k$ 场比赛 A 就一定能赢（A 能全部取 $100$）。

$$(n+k)-\lfloor\frac{n+k}{4}\rfloor\ge k$$

$$k\leq3n$$

所以我们只用模拟到 $3n$ 即可。

现将原数列从大到小排序，统计前缀和，判断是否能直接大于等于。

称排序过后的序列为原序列。

开始模拟：

- $i$ 从 $1$ 循环到 $2n-1$，表示增加的场数。

- 统计现在能选的场数 $(n+i)-\lfloor\frac{n+i}{4}\rfloor$。

- 对于 A，尽可能地取后面的数（大于 $n$ 的数），因为后面安排的全是 $100$，即：取 $n-\lfloor\frac{n+i}{4}\rfloor$ 个原序列最大的和 $i$ 个 $100$。

- 对于 B，由于后面安排的全是 $0$，所以取 $(n+i)-\lfloor\frac{n+i}{4}\rfloor$ 个最大的一定是原序列的前 $min((n+i)-\lfloor\frac{n+i}{4}\rfloor,n)$ 项的和。

- 若 $1$ 到 $2n-1$ 都不能满足大于等于，则输出 $3n$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int t,n,a[MAXN],b[MAXN],suma[MAXN],sumb[MAXN];
bool cmp(int x,int y){
	return x>y;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;++i){
			cin>>a[i];
			suma[i]=0;
		}
		for(int i=1;i<=n;++i){
			cin>>b[i];
			sumb[i]=0;
		}
		sort(a+1,a+n+1,cmp);
		sort(b+1,b+n+1,cmp);
		int tmp=n-n/4,tmpp;
		for(int i=1;i<=n;++i){
			suma[i]=suma[i-1]+a[i];
			sumb[i]=sumb[i-1]+b[i];
		}
		if(suma[tmp]>=sumb[tmp]){puts("0");continue;}
		bool f=1;
		for(int i=1;i<2*n;++i){
			tmp=n+i-(n+i)/4;
			if(suma[tmp-i]+i*100>=sumb[min(tmp,n)]){
				f=0;cout<<i<<endl;
				break;
			}
		}
		if(f)cout<<3*n<<endl;
	}
	return 0;
}
```

---

## 作者：Troubadour (赞：2)

这篇题解写于比赛次日，但是过了近两个周洛谷才把题爬出来。

赛场上一看这道题就感觉像是直接推式子的，但是我懒得推，所以用另一种可能近乎乱搞的方式把它过掉了。

我们贪心的想一下，如果我们想要尽量快的胜出，最好的情况就是后面的几次比拼中，自己全部拿 $100$ 分，对手全部拿 $0$ 分。所以问题就变成了：我们给自己加多少个 $100$，给对手加上相同数量的 $0$，可以使自己的成绩大于等于对手的。

很容易看出，假如一开始落后于对手，接下来~~近乎欺负人的~~加分，加的越多，和对手的差距就越小，最终追赶超越。感性推理可得，答案满足单调性，所以我们可以二分答案。

再一看，值域 $[0,100]$，非常友好。我们可以想到，对两个人分别开一棵权值线段树记录当前位置的和，每次加多少个 $0$ 或 $100$ 就加在对应位置上，开两个 $\mathrm{cnt}$ 数组分别记录每个数出现次数，计算时取出最大的 $k-\lfloor \frac{k}{4} \rfloor$ 个数分别求和比较就可以了。算完之后把加的数再删掉，就给对应位置减去这么多个数即可。

但是我们发现一个问题，就是在取数的边界上，数字可能取不完。比如你要拿 $3$ 个 $a$，可是 $a$ 这个数出现了 $5$ 次，这种情况下线段树是难以处理的。遇到这种情况，我们就直接在线段树上查 $[a+1,100]$ 这段区间的和，再加上剩下的部分，比如说刚才提到的 $3$ 个 $a$。具体怎么算，其实也可以二分，但是我还是懒得打了，就直接从 $1$ 到 $100$ 遍历 $\mathrm {cnt}$ 数组，直接算。在下面的代码里，为了方便，我把刚好取完边界数字也这样处理了。

**注意多组数据**，每次可以重新 $\mathrm{build}$ 一下清空数据，并清空 $\mathrm{cnt}$ 数组。

### Code：
```cpp
#include<bits/stdc++.h>
namespace CCCP
{
	const int N = 1005;
	int cnt[2][105];
	int n;
	struct seg
	{
		int l, r, sum;
	}f[2][N];//刻在基因里的线段树，0表示自己的，1表示对手的，下同
	void update(int k, int p)
	{
		f[k][p].sum = f[k][p << 1].sum + f[k][p << 1 | 1].sum;
	}
	void build(int k, int p, int l, int r)
	{
		f[k][p].l = l;f[k][p].r = r;
		if (l == r)
		{
			f[k][p].sum = 0;
			return;
		}
		int mid = (l + r) >> 1;
		build(k, p << 1, l, mid);
		build(k, p << 1 | 1, mid + 1, r);
		update(k, p);
	}
	void modify(int k, int p, int l, int r, int t)
	{
		if (l <= f[k][p].l&&f[k][p].r <= r)
		{
			f[k][p].sum += t * l;
			return;
		}
		int mid = (f[k][p].l + f[k][p].r) >> 1;
		if (mid >= l)modify(k, p << 1, l, r, t);
		if(mid<r) modify(k, p << 1 | 1, l, r, t);
		update(k, p);
	}
	int query(int k, int p, int l, int r)
	{
		if (l > r)return 0;
		if (l <= f[k][p].l&&f[k][p].r <= r)
		{
			return f[k][p].sum;
		}
		int res = 0;
		int mid = (f[k][p].l + f[k][p].r) >> 1;
		if (mid >= l)res += query(k, p << 1, l, r);
		if (mid < r)res += query(k, p << 1 | 1, l, r);
		return res;
	}
	bool judge(int k)
	{
		int ans[2] = { 0,0 };
		modify(0, 1, 100, 100, k);
		cnt[0][100] += k;
		modify(1, 1, 0, 0, k);
		cnt[1][0] += k;//自己加k个100，对面加k个0
		for (int i = 0;i <= 1;i++)
		{
			int j, tot = 0, num = (n + k) / 4;
			for (j = 0;j <= 100;j++)//这里改成二分应该更优，但是赛场上我懒得加了，各位可以优化一下
			{
				if (tot + cnt[i][j] < num)tot += cnt[i][j];
				else break;
			}
			ans[i] = query(i, 1, j + 1, 100) + (cnt[i][j]-num + tot)*j;//线段树上查[j+1,100]的和，再加上j的和就是这个人的得分
		}
		modify(0, 1, 100, 100, -k);
		cnt[0][100] -= k;
		modify(1, 1, 0, 0, -k);
		cnt[1][0] -= k;//把加上的再去掉
		return ans[0] >= ans[1];
	}
	void work()
	{
		memset(cnt, 0, sizeof(cnt));
		build(0, 1, 0, 100);
		build(1, 1, 0, 100);
		using std::cin;
		cin >> n;
		for (int i = 0;i <= 1;i++)
		{
			for (int j = 1;j <= n;j++)
			{
				int t;
				cin >> t;
				cnt[i][t]++;
				modify(i, 1, t, t, 1);
			}
		}
		int l = 0, r = 1e6, ans = 0;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (judge(mid))r = mid - 1,ans = mid;
			else l = mid + 1;
		}
		std::cout << ans << '\n';
	}
}
int main()
{
	int t;
	std::cin >> t;
	while (t--)CCCP::work();
	return 0;
}
```
CF 标签 `binary search`、`greedy`、`sortings`，那看来这个做法还挺接近正解的。没试过推式子的做法，估计也是可行的。

---

## 作者：Superiority (赞：0)

# 思路

考虑贪心思想，因为每个阶段可以获得的一个分数在 $0 \sim 100$，我们要使追上伊利亚的回合尽量少，那就使对方每个阶段获得分数尽量少，自己则多。再由于每个阶段获得的分数在 $0 \sim 100$ 之间，所以每次自己获得 $100$ 的分数，对方则获得 $0$ 的分数。

然后，接下来的步骤就是一个模拟。模拟每一个阶段，直到自己的分数大于对方时，这个时候答案就为这时的阶段数。

- 注意：设此时执行了 $k$ 阶段，若 $k$ 为 $4$ 的倍数时，要将自己最差的成绩减去。而对方，由于每个阶段都获得分数是 $0$，所以依旧没有改变。

这个模拟的时间复杂度，不难推出每次询问的最坏时间复杂度 $\Theta (n + n \log  n)$。所以直接模拟是可以过了此题的。

---

## 作者：Lizj (赞：0)

### 题面简述

给出你和对手的长度皆为 $n$ 个阶段的成绩序列，每个成绩都为 $0$ 到 $100$ 间的正整数。问至少再过多少个阶段，你的总分才能不小于对手的总分，如果你的总分已经不小于对手，输出 $0$。

总分的计算方式为：设当前已进行 $k$ 个阶段，则总分为最高的 $k-\lfloor \frac{k}{4} \rfloor$ 个阶段的成绩之和，其中，$\lfloor a \rfloor$ 表示 $a$ 向下取整（不大于 $a$ 的最大整数）。

### 分析

可以发现，要让阶段数最少，最优的方案是接下来每一轮都给自己加 $100$ 分，给对手加 $0$ 分。同理，当每组都按以上方案加分时，无论当前自己分数多低，对手分数多高，都可以在按最优方案加分后在 $n$ 个阶段内完成任务。

先对原成绩序列排序，每一轮加分结束后累加得分，直接进行模拟，单组数据时间复杂度为 $O(n+n \log_2 n)$，总时间复杂度为 $O(\sum n+n \log_2 n)$，以下给出模拟步骤：

1. 将成绩序列排序；

1. 自己总分每阶段加 $100$，当阶段数为 $4$ 的倍数时，减去当前最差成绩；

1. 类似地，在对手 **成绩序列** 中每阶段加 $0$ 后，计算总分。由于每阶段的加分都为 $0$，所以总分只会加原成绩序列中的分数，当阶段数为 $4$ 的倍数时，不进行操作即可。

在模拟的过程中进行比较，大于等于对方分数后输出当前次数即可。至此，我们通过了该题。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],b[100010];
int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=n;i++){
            cin>>b[i];
        }
        sort(a+1,a+n+1);    //升序排列
        sort(b+1,b+n+1);
        int cnt=n,ans=0;
        int s1=0,s2=0;
        int p1=n/4+1,p2=n/4+1;
        for(int i=n/4+1;i<=n;i++){  //求出当前成绩
            s1+=a[i];
            s2+=b[i];
        }
        while(s1<s2){   //目标为不小于对手分数
            s1+=100,ans++,cnt++;    //自己新成绩为100
            if(cnt%4==0){   //求出新成绩
                if(p1>=n)   //超出原序列，都为100分
                    s1-=100;
                else    //未超出原数列，减去原数列中成绩
                    s1-=a[p1++];
            }
            if(p2&&cnt%4!=0){
                s2+=b[--p2];    //对手新成绩为0，与自己成绩相差最大：贪心思想，保证答案最优
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1530C](https://www.luogu.com.cn/problem/CF1530C)

* **【解题思路】**

其实这题不用桶，不用权值线段树。

这个东西就是一步步模拟，**纯粹的模拟题。**

既然要说最好情况，那么肯定是之后你每次都 $100$ 分，Ilya 每次都 $0$ 分。

那么，我们开始把输入的分数都先排一下序，然后记一下总分，一步步模拟。

具体过程：

1. 把两人的分数升序排序，并计算总分（注意要减去分值最小的 $\lfloor\frac{n}{4}\rfloor$ 个分值）。检查总分是否已经符合条件。

2. 之后一步步模拟进行的回合。每次，给自己加 $100$ 分，对手的的分不变。
	
	如果这一次的回合编号能被 $4$ 整除，那么，你就要舍弃一个最低分（用指针维护当前最低分的位置，每舍弃一个就加 $1$），如果开始给出的分数已经舍弃完了，就只能舍弃一个 $100$ 分。
	
    否则，对手就会多一个 $0$ 分舍弃，她的总分就可以加上她目前最低的分数（同样用指针维护，只不过换成减 $1$），如果开始给出的分数已经全部加完，那么她的分数就只能不变了。
    
3. 检查自己的得分是否超过对手的得分。如果不是，回到第 $2$ 步。如果是，输出当前局数，结束这一次测试。

那么，这样一个纯粹的模拟大暴力，为什么可以最大点 $110\text{ms}$ 过？

很简单。它的复杂度是对的。

即使是一个纯粹的模拟，最多模拟的局数是在自己全是 $0$ 分而对手全部 $100$ 的时候。这时，我们要模拟 $n$ 局。在这种情况下，复杂度是 $\mathcal O(n)$ 的。

而题目中，$n$ 的和最大仅有 $10^6$。在极限数据下，最差复杂度也仅是 $\mathcal O(n+n\log_2n)$（而且这个带 $\log$ 的部分还是`std::sort`给的），再加上 $2\text s$ 的时限，常数再大都不怕跑不过。

现在我们的这个大暴力，复杂度是 $\mathcal O(\sum n+n\log_2n)$，可以通过，毫无压力。

* **【代码实现】**

```cpp
#include <array>
#include <iostream>
#include <algorithm>

using namespace std;

array<int,100000> my_sc,llya_sc;

int main(int argc,char *argv[],char *envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt_cnt,test_cnt,least_r,my_score,llya_score,my_iter,llya_iter;
	cin>>testcnt_cnt;
	while(testcnt_cnt--)
	{
		least_r=0;
		cin>>test_cnt;
		for(int i=0;i<test_cnt;i++)
			cin>>my_sc[i];
		for(int i=0;i<test_cnt;i++)
			cin>>llya_sc[i];
		sort(my_sc.begin(),my_sc.begin()+test_cnt),sort(llya_sc.begin(),llya_sc.begin()+test_cnt);
		my_score=accumulate(my_sc.begin()+test_cnt/4,my_sc.begin()+test_cnt,0),llya_score=accumulate(llya_sc.begin()+test_cnt/4,llya_sc.begin()+test_cnt,0);
		my_iter=llya_iter=test_cnt/4;
		while(my_score<llya_score)//快乐暴力模拟
		{
			my_score+=100,least_r++,test_cnt++;
			if(test_cnt%4==0)
			{
				if(my_iter==test_cnt-1)
					my_score-=100;
				else
					my_score-=my_sc[my_iter++];
			}
			if(llya_iter&&test_cnt%4)
				llya_score+=llya_sc[--llya_iter];
		}
		cout<<least_r<<'\n';
	}
 	return 0;
}

```

---

## 作者：cyrxdzj (赞：0)

### 一、题目翻译

[在这里！](https://www.luogu.com.cn/paste/hnedi1o7)

### 二、思路

本题，我的思路真的是一步一步模拟。

但是，模拟也是要有优化的。

首先，如果“我”的初始总分比伊利亚低，那么，接下来的几个阶段，“我”的分数一定要是 $100$ 分，伊利亚的分数一定要是 $0$ 分（废话）。

既然如此，我们就可以模拟出之后的每个阶段的得分情况。

但是，如果只单纯地用数组存储分数，再用排序加暴力求和，那么你就可以收获 TLE+MLE 双重暴击。

那怎么办？

看看题，每个人的分数都在 $0$ 到 $100$ 之间，且还是整数。

疯狂暗示我们使用桶！

与之相似的题目：[P7072 直播获奖](https://www.luogu.com.cn/problem/P7072)。

所以，我们就可以建两个桶，代表“我”和伊利亚的得分分布。

每一阶段，“我”的 $100$ 分获得次数加 $1$，伊利亚的 $0$ 分获得次数加 $1$。

然后，再使用复杂度极低的加法乘法搭配，求出“我”的总分与伊利亚的总分。如果达到了目标，输出答案即可。

### 三、完整代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int n;
int get_result(int tong[101],int n)
{
	register int num=n-n/4;//需要计入总分的阶段数。
	register int ans=0;
	for(register int i=100;i>=0;i--)//计算总和。
	{
		if(tong[i]<=num)
		{
			ans+=i*tong[i];
			num-=tong[i];
		}
		else
		{
			ans+=num*i;
			break;
		}
	}
	return ans;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		int tong1[101],tong2[101];
		memset(tong1,0,sizeof(tong1));//记得初始化！
		memset(tong2,0,sizeof(tong2));
		register int input;
		for(register int i=1;i<=n;i++)//输入。
		{
			scanf("%d",&input);
			tong1[input]++;
		}
		for(register int i=1;i<=n;i++)
		{
			scanf("%d",&input);
			tong2[input]++;
		}
		register int result1=get_result(tong1,n),result2=get_result(tong2,n);//先算一遍总分。
		if(result1>=result2)
		{
			printf("0\n");
			continue;
		}
		for(register int i=n+1;;i++)
		{
			tong1[100]++;
			tong2[0]++;//思考：删掉这行，对运行输出有影响吗？
			result1=get_result(tong1,i);
			result2=get_result(tong2,i);
			if(result1>=result2)
			{
				printf("%d\n",i-n);
				break;
			}
		}
	}
	return 0;//完结撒花！
}

```

### 四、思考题答案

当然不会。

 $0$ 乘以任何数都得 $0$，这是小学的数学知识。
 
 并且，$0$ 分是计算总分的最后一步，因此，无论如何，就算影响了第 $15$ 行中 `num` 变量，也没有影响。顶多是 `num` 变量最后大于 $0$，但这又如何？
 
 By [dengzijun](https://www.luogu.com.cn/user/387836)

---

