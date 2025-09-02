# [ARC008B] 謎のたこ焼きおじさん

## 题目描述

你来买章鱼烧的时候，得到了传说中的章鱼烧大师——章鱼烧店的老板高桥先生的认可，被任命为新的章鱼烧店的老板。

你被任命为店长后的第一份工作就是制作店铺的招牌。

现在章鱼烧店的名字已经决定好了，制作招牌的任务就交给了你。

因此这时候高桥老板就给了你几个制作招牌要用的英文字母配件包。

英文字母配件包指的是含有随机英文字母的袋子。

例如：当英文字母配件包表示为字符串ABCC的时候可以被认作是：
- 包含1个英文字母A
- 1个英文字母B
- 和2个英文字母C

也就是说，对于一袋英文配件包ABCC，1个英文字母A、1个英文字母B和2个英文字母C都可以被用于制作招牌。

因为从高桥老板那里得到的英文字母配件包都是相同的，所以打开任何一个英文字母配件包里面的东西也都是一样的。

你不想在制作招牌上花太多的钱，因此要使用尽量少的英文字母配件包，并把剩下的退货。

究竟用多少的英文字母配件包就可以完成招牌的制作呢？

## 说明/提示

- 样例1：因为英文字母配件包ABCDEFGHIJKLMNOPQRSTUVWXYZ内只含有一个O，因此制作招牌NAOHIRO需要两个配件包。
- 样例2：只用一个配件包TAKOYAKI就可以制作完成招牌TAKOYAKI。
- 样例3：英文字母配件包MYON内没有英文字母C,H,K,U,D,A,I，因此无法成功制作招牌。所以输出-1。
- 样例4：替换一下英文字母配件包NAMAKO内的字母顺序，便正好可以制作招牌。

# 题解

## 作者：nanatsuhi (赞：2)

这道题非常简单，不过有一点需要注意的地方：

- 除以零的RuntimeError
- -1判定条件

除此之外就是道简单模拟。

~~顺便一说：我认为长度毫无意义可言，不过给都给了还是用一下比较好~~ 

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int snum[26],bnum[26]; //分别统计A到Z的次数，s是招牌，b是配件包
int main()
{
    int n,m,ans=0;//ans显然取最大值，那么初值就设成0
    cin>>n>>m;
    for(int i=0;i<n;i++) 
    {
        char c;
        cin>>c;
        snum[c-'A']++; //对应字母的下标
    }
    for(int i=0;i<m;i++) 
    {
        char c;
        cin>>c;
        bnum[c-'A']++; //同理
    }
    for(int i=0;i<26;i++)
    {
        if(bnum[i]==0&&snum[i]>0) 
        { //条件：包里没有而招牌需要
            cout<<"-1";
            return 0;
        }
        if(!(bnum[i]|snum[i])) continue; //就是都是0的判定，不加会RE
        if(snum[i]%bnum[i]) ans=max(ans,snum[i]/bnum[i]+1); //非整除
        else ans=max(ans,snum[i]/bnum[i]);
    }
    cout<<ans;
    return !((false^true)|(true&false)); //圆满结束
}
```


---

## 作者：yzc0x13269d6 (赞：1)

~~本蒟蒻不会用大佬们高深的办法，所以来介绍一种笨办法——纯模拟~~

为了避开除以0，本蒟蒻使用了累加的办法。首先输入，统计需要的各个字母的个数以及每个配件包内的各个字母的个数，然后来个没有条件的`for`循环，每次分别累加每个配件包内的各个字母的个数，并判断各个字母现有个数是否不小于需要的个数，如果够了，则输出结果，然后`return 0`。$ \text{\color{red}{但是请注意：在循环累加之前，必须要检查是否能够组成招牌！}} $我个人不喜欢用$ \verb!string! $类，所以使用`strchr()`函数来检查字符串里是否含有某字符。

$ \verb!Code:! $
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int cnt[30],cnt2[30],n,m,t[30];
//cnt是存储需要的各字母个数，cnt2是存储每个配件包里的字母个数，t是存储累加时目前的字母个数
char bag[55],sign[55];
bool is_enough() {
	for(int i = 0;i < n;i++) {
		if(t[sign[i] - 64] < cnt[sign[i] - 64]) return 0;
	}
	return 1;
} //为了方便，把判断是否足够的代码写到函数里
int main() {
	scanf("%d%d",&n,&m);
	scanf("%s",sign);
	for(int i = 0;i < n;i++) cnt[sign[i] - 64]++;
	scanf("%s",bag);
	for(int i = 0;i < m;i++) cnt2[bag[i] - 64]++;
	//输入并统计
	for(int i = 0;i < n;i++) {
		if(strchr(bag,sign[i]) == NULL) {
			printf("-1\n");
			return 0;
		}
	}
	//提前判断
	for(int i = 1;;i++) {
		for(int j = 1;j <= 26;j++) t[j] += cnt2[j]; //累加 
		if(is_enough()) {
			printf("%d\n",i);
			return 0;
		} //判断是否够了 
	}
	return 0;
}
```

---

## 作者：little_rubbish (赞：0)

## 思路
存储每个字母分别在配件包和招牌里出现的次数，然后枚举每个字母分别在招牌和配件包出现的次数，计算每个字母要几个配件包，求出答案。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std; 
int n,m;
int a[27],b[27],ans=-999;
char x;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>x;
		a[x-'A'+1]++;//计算每个字母出现的次数
	}
	for(int i=1;i<=m;i++){
		cin>>x;
		b[x-'A'+1]++;//计算每个字母出现的次数
	}
	for(int i=1;i<=26;i++){//枚举26个字母
		if((a[i])&&(!b[i])){//如果招牌里有可配件包没有就算再多配件包也没用
			cout<<-1;
			return 0;
		}
		if(!a[i]&&!b[i])continue;//都没出现这个字母的话，跳过
		ans=max(ans,(int)(ceil(1.0*a[i]/b[i])));//先用double运算，然后强制转换成int，要向上取整，包数是整数
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：makerlife (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT278) | [AT 原题传送门](https://atcoder.jp/contests/arc008/tasks/arc008_2)

## 思路

这道题考察了**桶**的思想。

定义两个桶，分别存放**给出招牌中的每个字母的数量**和**配件包中的每个字母的数量**

有两个小问题需要注意：

1. 当招牌需要这个字母，而配件包里没有，直接输出 $-1$ 并结束程序；

2. 需要特判当配件包里的每个字符数量如果是 $0$，就要跳过本次循环，避免除数为 $0$。

思路不难，看看代码和注释就能理解吧

## 代码

```cpp
#include<cmath>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int ta[30],tb[30];
int n,m;
string a,b;
int maxn=-1;
int main()
{
	cin>>n>>m;
	cin>>a>>b;
	for(int i=0;i<n;i++)
	{
		ta[a[i]-'A'+1]++;
	}
	for(int i=0;i<m;i++)
	{
		tb[b[i]-'A'+1]++;
	}
	//上面的两个循环是桶的初始化，记录字符出现的数量
	for(int i=1;i<=26;i++)
	{
		if(ta[i]!=0 && tb[i]==0)//特判输出 -1 的条件
		{
			cout<<-1<<endl;
			return 0;
		}
		if(ta[i]==0 && tb[i]==0)//特判除数为 0 时的情况
		{
			continue;
		}
		maxn=max(maxn,(int)(ceil(1.0*ta[i]/tb[i])));//直接进行计算
	}
	cout<<maxn<<endl;
	return 0;
}

```

求管理大大通过

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT278)

小学生又双叒叕来写题解啦！

我的思路是，先统计招牌与材料包中不同字母的数量。

然后，枚举二十六个字母。

对于每个字母，用招牌字母数除以材料包字母数，再**向上取整**。

这样可以得到单个字母所需的材料包数量。

取这些数中**最大值**即可。

还有两个问题。

一是如何**判断无解**。

只需在枚举过程中检查，若招牌里需要某字母，但材料包里没有，显然无法制作。

但第二个问题很容易忽略。

如果在招牌字母数除以材料包字母数的时候，材料包字母数恰为零，这可怎么办？

因此，为了提防除以零的尴尬情况，我们需要特判。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int cntS[35], cntG[35];
int main()
{
	//以下为输入，并且存储字母个数。 
	int lenS, lenG;
	scanf("%d%d", &lenS, &lenG);
	string s, g;
	cin >> s >> g;
	for (int i = 0; i < lenS; i++) cntS[s[i] - 'A' + 1]++;
	for (int i = 0; i < lenG; i++) cntG[g[i] - 'A' + 1]++;
	
	int maxn = -1;
	for (int i = 1; i <= 26; i++)
	{
		if (cntS[i] != 0 && cntG[i] == 0)  //招牌需要，但材料包里没有。 
		{
			printf("-1\n");
			return 0;
		}
		if (cntS[i] == 0 && cntG[i] == 0) continue;  //防止除零事件发生。 
		int t = ceil(1.0 * cntS[i] / cntG[i]);
		maxn = max(maxn, t);
	}
	printf("%d\n", maxn);  //题目要求要换行。 
	return 0;
}
```


---

## 作者：a1029 (赞：0)

### 看各位大佬都在写桶排序，我也来占个位。


先来说一下我的想法。

本人认为这道题实在不需要桶排序，只需要掌握字符串函数 find() 即可。

主要是先用一个字符串 t 来保存原始的英文配件包（以下简称 b ），如果店名（以下简称 a ）里的某个字符连 t 里都找不到，只好输出 -1 。

然后每当 b 里发现一个 a 里的字符，就把 b 这个位置的字符换成 '@' 。当 b 里的配件不够时，就再加上 t （加一个配件包，同时 ans++ ）。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int ans = 1;
	string a, b, t;
	cin >> a >> b >> a >> b;
	t = b;
	for (int i = 0; i < a.size(); i++) {
		if (t.find(a[i]) == t.npos) {
			puts("-1");
			return 0;
		}
		if (b.find(a[i]) != b.npos) b[b.find(a[i])] = '@';
		else {
			ans++;
			b += t;
			i--;
			continue;
		}
	}
	cout << ans;
	return 0;
}

```


------------
别忘了 endl

---

## 作者：LiveZoom (赞：0)

# 题解 AT278 【謎のたこ焼きおじさん】
此题是对字符串的考查，貌似夹杂着对“桶”的考察。
## Solution
我们用mpa,mpb两个桶来记录a,b中出现的字符个数，然后枚举就行了（不过有几个小坑要注意）。
## Code
初始化mpa,mpb:

```cpp
	cin>>a>>b;
	int mpa[26]={0},mpb[26]={0};
	for(int i=0;i<b.size();i++){
		mpb[b[i]-'A']++;
	}
	for(int i=0;i<a.size();i++){
		mpa[a[i]-'A']++;
	}
```

枚举：

```cpp
	int ans=0;//定义ans=0
	for(int i=0;i<26;i++){
		if(mpb[i]==0&&mpa[i]>0){//如果没有此配件
			puts("-1");//输出-1结束
			return 0;
		}
		if(mpb[i]==0||mpa[i]==0)continue;//注意！两个有一个为零就不能继续了，卡了我好久
		ans=max(ans,cei(mpa[i],mpb[i]));//没什么说的，cei函数就是ceil自己写的
	}
	printf("%d\n",ans);
```

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int cei(int m,int n){
	if(m%n==0)return m/n;
	else return m/n+1;
}
int main()
{
	int n,m;
	cin>>n>>m;
	cin>>a>>b;
	int mpa[26]={0},mpb[26]={0};
	for(int i=0;i<b.size();i++){
		mpb[b[i]-'A']++;
	}
	for(int i=0;i<a.size();i++){
		mpa[a[i]-'A']++;
	}
	int ans=0;
	for(int i=0;i<26;i++){
		if(mpb[i]==0&&mpa[i]>0){
			puts("-1");
			return 0;
		}
		if(mpb[i]==0||mpa[i]==0)continue;
		ans=max(ans,cei(mpa[i],mpb[i]));
	}
	printf("%d\n",ans);
    return 0;
}
```
求通过
# The end

---

## 作者：智子·起源 (赞：0)

为什么没有简单一点的写法呢？

```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int n,m,s[100],ss[100],ans;
string a,b; 
int main()
{
  scanf("%d%d",&n,&m);cin>>a>>b;//读入字符串与长度。
  for(int i=0;i<m;i++)s[b[i]]++;//记录配件包各个零件的数量
  for(int i=0;i<n;i++)ss[a[i]]++;//记录招牌需要各个零件的数量
  for(int i=65;i<65+26;i++)//每一种零件开始枚举找需要配件包的数量
  {
    if(s[i]==0&&ss[i]!=0){printf("-1\n");return 0;}//如果配件包该零件数量为0而招牌又需要用该零件的话，那就证明招牌无法建成。
    if(s[i]==0)continue;//如果配件包零件数量还是0，那就是说，招牌需要零件数量数量还是0，没必要操作。（也预防了下面0作除数的出错情况）
    ans=max(ans,ss[i]/s[i]+(ss[i]%s[i]>0));//计算需要几个配件包，并更新需要配件包数量的最大值。
  }
  printf("%d\n",ans);//输出ans
  return 0;
}

```

要注意一点的是：程序中更新最大值中的“(ss[i]%s[i]>0)”的意思是看一下余数是否大于0，大于的话就返回1，否则返回0，加上余数的那份。

该程序明显比下面的简单很多。

下面是源代码：（不加注释）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s[100],ss[100],ans=-1;string a,b; 
int main()
{
  scanf("%d%d",&n,&m);cin>>a>>b;
  for(int i=0;i<m;i++)s[b[i]]++;
  for(int i=0;i<n;i++)ss[a[i]]++;
  for(int i=65;i<65+26;i++)
  {
    if(s[i]==0&&ss[i]!=0){printf("-1\n");return 0;}
    if(s[i]==0)continue;
    ans=max(ans,ss[i]/s[i]+(ss[i]%s[i]>0));
  }
  printf("%d\n",ans);
  return 0;
}

```


---

