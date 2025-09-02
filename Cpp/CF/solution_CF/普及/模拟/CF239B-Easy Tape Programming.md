# Easy Tape Programming

## 题目描述

There is a programming language in which every program is a non-empty sequence of "<" and ">" signs and digits. Let's explain how the interpreter of this programming language works. A program is interpreted using movement of instruction pointer (IP) which consists of two parts.

- Current character pointer (CP);
- Direction pointer (DP) which can point left or right;

Initially CP points to the leftmost character of the sequence and DP points to the right.

We repeat the following steps until the first moment that CP points to somewhere outside the sequence.

- If CP is pointing to a digit the interpreter prints that digit then CP moves one step according to the direction of DP. After that the value of the printed digit in the sequence decreases by one. If the printed digit was $ 0 $ then it cannot be decreased therefore it's erased from the sequence and the length of the sequence decreases by one.
- If CP is pointing to "<" or ">" then the direction of DP changes to "left" or "right" correspondingly. Then CP moves one step according to DP. If the new character that CP is pointing to is "<" or ">" then the previous character will be erased from the sequence.

If at any moment the CP goes outside of the sequence the execution is terminated.

It's obvious the every program in this language terminates after some steps.

We have a sequence $ s_{1},s_{2},...,s_{n} $ of "<", ">" and digits. You should answer $ q $ queries. Each query gives you $ l $ and $ r $ and asks how many of each digit will be printed if we run the sequence $ s_{l},s_{l+1},...,s_{r} $ as an independent program in this language.

## 样例 #1

### 输入

```
7 4
1>3>22<
1 3
4 7
7 7
1 7```

### 输出

```
0 1 0 1 0 0 0 0 0 0 
2 2 2 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
2 3 2 1 0 0 0 0 0 0 
```

# 题解

## 作者：GUO120822 (赞：1)

 [题目传送门](https://www.luogu.com.cn/problem/CF239B)

这道题真难懂，英译过来的。

题目理解错了好几遍（虽然这题只是个小模拟）。
# 思路
模拟。

对于每次询问，执行 $l$ 到 $r$ 的序列。

每次都往相应方向走，如果遇到两个符号，则方向变为相应方向，删除（标记为特殊字符），再在走的过程中记录。
# 易错点
1. 题目中的“前”是时间上的前，不是位置上的前。

2. 出边界了就立马退出，否则会死循环。

3. 每次的计数数组要清零。

4. 查找的过程是改变方向之后在查找，而不是一开始就找。

$l$：兼输入中的 $l$ 和 $cp$。

$r$：兼输入中的 $r$ 和 $dp$。

$cnt$：计数数组。

$a$：初始数组。

$s$：截取数组，长度为 $k$。
### 调了好几次才调出来。

[AC](https://www.luogu.com.cn/record/132780493)

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,l,r,i,cnt[10],p;
char a[110],s[110],k;
int work(int x)
{
	while (s[x]=='#'&&x>=1&&x<=k) x+=r;
	return x;
}
int main()
{
	scanf("%d%d%s",&n,&q,a+1);
	while (q--)
	{
		scanf("%d%d",&l,&r);
		k=0;
		memset(cnt,0,sizeof(cnt));
		for (i=l;i<=r;i++) s[++k]=a[i];
		l=r=1;
		while (1)
		{
			if (isdigit(s[l]))
			{
				cnt[s[l]-'0']++;
				if (s[l]=='0') s[l]='#';
				else s[l]--;
				p=work(l+r);
				if (p<1||p>k) break;
			}
			else if (s[l]=='<'||s[l]=='>')
			{
				if (s[l]=='<') r=-1;
				else r=1;
				p=work(l+r);
				if (p<1||p>k) break;
				if (s[p]=='<'||s[p]=='>') s[l]='#';
			}
			l=p;
		}
		for (i=0;i<=9;i++) printf("%d ",cnt[i]);
		printf("\n");
	}
	return 0; 
}
```

---

## 作者：RE_Prince (赞：0)

# CF239B Easy Tape Programming

[link](https://www.luogu.com.cn/problem/CF239B)

## Sol

思路：字符串暴力。

每次按照题目给的 CP DP 方向来模拟，删除的处理方法就是拿一个数组标记一个下标是否被删除。如果是，那就不停地往 DP 的方向去枚举，直到找到了一个没有被标记的地方或者判断越界。

注意一下，在减 $s_i$ 的时候，要记录一下原始的 $s$ 数组，否则多测会爆零。还有，当 $s_i=0$，在输出的 $0$ 的次数也要加。 

具体看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,k,cnt[19];
bool d[109];
char s[109];
int main()
{
	int t;
	cin>>n>>t;
	cin>>s+1;
	while(t--)
	{
		memset(cnt,0,sizeof(cnt));//清空！
		memset(d,0,sizeof(d));
		char f[109];
		for(i=1;i<=n;i++) f[i]=s[i];//赋初值
		int l,r;
		cin>>l>>r;
		int pl=l,dp=1;
		while(1)
		{
		//	cout<<pl<<" ";
			if(isdigit(f[pl]))//如果是数字
			{
				if(f[pl]=='0')//如果到头了，删除
				{
					d[pl]=1;//标记删除
				//	puts("now");
					cnt[0]++;
					
					pl+=dp;
					while(d[pl]) pl+=dp;
					if(pl<l||pl>r) break;//判断越界
				}
				else 
				{
					cnt[f[pl]-'0']++;
					int now=pl;
					pl+=dp;
					while(d[pl]) pl+=dp;
					if(pl<l||pl>r) break;
					f[now]--;
				}
			}
			else
			{
			//	puts("<>");
				if(f[pl]=='<') dp=-1;//更改方向
				else if(f[pl]=='>') dp=1;
		//		cout<<f[pl]<<" "<<pl<<" "<<dp<<endl;
				int now=pl;
				pl+=dp;
				while(d[pl]) pl+=dp;//找到第一个没有被标记的
				if(pl>r||pl<l) break;
				if(f[pl]=='<'||f[pl]=='>') d[now]=1;//删除以前的字符
			}
		}
		for(i=0;i<=9;i++) cout<<cnt[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：0)

字符串模拟，暴力模拟即可。

注意记录上一个字符不要记录已经删除的。

模拟题没有什么好说的，具体的思路看代码里面的注释吧。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,q;
int l,r,now,last;
bool f,f1;
char str[110],ch[110];
int vis[10];
void solve()
{
	for(int i=1;i<=n;i++)
		ch[i]=str[i];
	//因为我们要修改字符串，有多组询问，所以把它拷贝到另一个字符串里 
	scanf("%d%d",&l,&r);
	now=last=l;
	//now为当前的指针指向位置，last为上次生效的now 
	f=0;
	//f代表上次是否为'<'或'>' 
	f1=1;
	//f1=1代表指针向右，否则为左 
	for(int i=0;i<=9;i++) vis[i]=0; 
	while(now>=l&&now<=r)
	{
		if(ch[now]>='0'&&ch[now]<='9') {//如果当前指向的是数字 
			vis[ch[now]-'0']++;//计数器+1 
			if(ch[now]!='0') ch[now]--;//如果不是'0'就自减1 
			else ch[now]='*';//否则删除字符，我选择赋值任意一个字符。 
			f=0;//这次now生效，但不为'<'或'>'
			last=now;//now生效，记录下来
		}
		if(ch[now]=='<') {
			f1=0;
			if(f) ch[last]='*';//如果上次为'<'或'>'且这次仍为，就删除字符 
			f=1;//now生效且为'<'或'>' 
			last=now;
		}
		if(ch[now]=='>') {//同上 
			f1=1;
			if(f) ch[last]='*';
			f=1;
			last=now;
		}
		if(f1) now++;//根据方向对now进行自增或自减 
		else now--;
	}
	for(int i=0;i<=9;i++)
		printf("%d ",vis[i]);
	puts("");
}
int main()
{
	scanf("%d%d",&n,&q);
	scanf("%s",str+1);
	while(q--)
		solve();
	return 0;
}
```


---

