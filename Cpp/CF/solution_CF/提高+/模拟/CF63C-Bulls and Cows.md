# Bulls and Cows

## 题目描述

The "Bulls and Cows" game needs two people to play. The thinker thinks of a number and the guesser tries to guess it.

The thinker thinks of a four-digit number in the decimal system. All the digits in the number are different and the number may have a leading zero. It can't have more than one leading zero, because all it's digits should be different. The guesser tries to guess the number. He makes a series of guesses, trying experimental numbers and receives answers from the first person in the format " $ x $ bulls $ y $ cows". $ x $ represents the number of digits in the experimental number that occupy the same positions as in the sought number. $ y $ represents the number of digits of the experimental number that present in the sought number, but occupy different positions. Naturally, the experimental numbers, as well as the sought number, are represented by four-digit numbers where all digits are different and a leading zero can be present.

For example, let's suppose that the thinker thought of the number 0123. Then the guessers' experimental number 1263 will receive a reply "1 bull 2 cows" (3 occupies the same positions in both numbers and 1 and 2 are present in both numbers but they occupy different positions). Also, the answer to number 8103 will be "2 bulls 1 cow" (analogically, 1 and 3 occupy the same positions and 0 occupies a different one).

When the guesser is answered "4 bulls 0 cows", the game is over.

Now the guesser has already made several guesses and wants to know whether his next guess can possibly be the last one.

## 样例 #1

### 输入

```
2
1263 1 2
8103 2 1
```

### 输出

```
Need more data```

## 样例 #2

### 输入

```
2
1234 2 2
1256 0 2
```

### 输出

```
2134```

## 样例 #3

### 输入

```
2
0123 1 1
4567 1 2
```

### 输出

```
Incorrect data```

# 题解

## 作者：ikunTLE (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/CF63C)

### 思路

题目中提到一个 4 位数，不难想到枚举 $0$ 到 $9999$ 所有的数，并统计其中成立的个数。由于题目中的 $n$ 很小，我们可以挨个判断。

若成立个数为 $0$，则输出 `Incorrect data`；若成立个数为 $1$，则输出答案；若成立个数 $\ge2$，则输出 `Need more data`。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=15,E=1e4,M=1e4+10,X=10;
int n,d[X],pos[N],num[N];
bool vis[N],flag[M];
string s[N];
int calc_num(){
	int res=0;
	for(int i=1;i<=4;++i)
		res=res*10+d[i];
	return res;
}
void solve(){
	int temp=calc_num();
	flag[temp]=true;
	for(int i=1;i<=n;++i){
		int cnt1=0,cnt2=0;
		for(int j=1;j<=4;++j)
			if(d[j]==s[i][j-1]-'0')
				++cnt1;
			else if(vis[s[i][j-1]-'0'])
				++cnt2;
		if(cnt1!=pos[i]||cnt2!=num[i])
			flag[temp]=false;
	}
	return;
}
void dfs(int x){
	if(x==5){
		solve();
		return;
	}
	for(int i=0;i<=9;++i)
		if(!vis[i]){
			vis[i]=true;
			d[x]=i;
			dfs(x+1);
			vis[i]=false;
		}
	return;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		cin>>s[i];
		pos[i]=read(),num[i]=read();
	}
	dfs(1);
	int cnt=0,ans=-1;
	for(int i=1;i<=E;++i)
		if(flag[i])
			++cnt,ans=i;
	if(!cnt)
		printf("Incorrect data\n");
	else if(cnt>=2)
		printf("Need more data\n");
	else printf("%04d\n",ans);
	return 0;
}
```

---

## 作者：FeiYu32 (赞：6)

根据题目标签显示，这题的正确做法很明显是 ———— 暴力！

其实不难理解，由于要求是四位数，即使算上前导零一共也只需要从一万个数，即从 $0000$ 到 $9999$ 中直接暴力代入条件判断是否符合条件即可，两秒的时间几乎不可能超时。

最后记录所有解的总数。如果无解输出```Incorrect data```，有唯一解时输出唯一解，有多解时输出```Need more data```。

对于如何判断是否满足条件，可以选择用数组来存数字拆开后每个数字的下标，然后与条件逐个对比即可。

除了前导零的坑点，题目总体来说并不难，蓝题貌似有些高了，作为上位黄差不多。

---

## 作者：wxzzzz (赞：5)

### 题意

给定 $n$ 组限制，求一个四位数，或者输出无解或多解。

每组限制先给定一个数，然后告诉你答案与这个数相同的位数，以及排序后相同的位数。

### 思路

枚举。

如果直接枚举数字还要考虑前导 $0$，因此枚举每一位。

然后需要考虑如下几点：

1. 判重。

1. 相同的位数。

1. 排序后相同的位数。

	根据容斥原理，排序后相同的位数 $=$ 各自拥有的相同的位数 $-$ 相同的位数。

最后特判一下，如果答案小于 $1000$，要补上前导 $0$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, cnt, ans, a[15], b[15];
char s[15][15];
bool check(int n1, int n2, int n3, int n4) {
    int now[4] = {n1, n2, n3, n4};

    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 4; j++)
            if (now[i] == now[j])
                return 0;

    for (int i = 1; i <= n; i++) {
        int has = 0, same = 0;

        for (int j = 0; j < 4; j++)
            if (now[j] + '0' == s[i][j])
                same++;

        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                if (now[j] + '0' == s[i][k]) {
                    has++;
                    break;
                }

        if (same != a[i] || has - same != b[i]) {
            return 0;
        }
    }

    ans = n1 * 1000 + n2 * 100 + n3 * 10 + n4;
    return 1;
}
int main() {
    cin >> n;

    for (int i = 1; i <= n; i++)
        scanf("%s", s[i]), cin >> a[i] >> b[i];

    for (int n1 = 0; n1 <= 9; n1++)
        for (int n2 = 0; n2 <= 9; n2++)
            for (int n3 = 0; n3 <= 9; n3++)
                for (int n4 = 0; n4 <= 9; n4++)
                    if (check(n1, n2, n3, n4))
                        cnt++;

    if (!cnt)
        puts("Incorrect data");
    else if (cnt > 1)
        puts("Need more data");
    else {
        if (ans < 1000)
            putchar('0');

        cout << ans;
    }

    return 0;
}
```

---

## 作者：AKPC (赞：4)

### 思路
这题我们直接**暴力出奇迹**。

首先如果要判断某个数字是否符合小 A 所说，即 `check()` 函数的写法，因为是暴力做法，不用想太多，直接匹配每次小 B 问的数字，然后计数看是否等于小 A 给的两个值就行了，这样的时间复杂度约为 $\text O(n)$。

接着就暴力枚举每个四位数，注意带有前导 $0$ 的不超过四位的数字也算四位数，总共有 $10^4$ 个四位数，也就是 $10^4$ 次枚举，然后对于每个数都进行一次 `check()`，如果符合条件就把计数器加一，并记录这个四位数。

最后就是如果计数器正好是 $1$ 就输出那个四位数，其他的按照题意来输出相应字符串即可，注意有些 $<1000$ 的四位数要输出前导 $0$ 补齐四位。

总时间复杂度约为 $\text O(10^4\times n)$，而 $n\leq10$ 显然不会超时。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0;bool f=1;register char c=getchar();
    while (c<48||c>57){if(c=='-') f=0;c=getchar();}
    while (c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
int n,cnt,ans,a[15],b[15];
string s[15];
bool check(int x,int y,int z,int w){
	int now[4]={x,y,z,w};
	for (int i=0;i<4;i++) for (int j=i+1;j<4;j++) if (now[i]==now[j]) return 0;
	for (int i=1;i<=n;i++){
		int has=0,same=0;
		for (int j=0;j<4;j++) if (now[j]+'0'==s[i][j]) same++;
		for (int j=0;j<4;j++) for (int k=0;k<4;k++) if (now[j]+'0'==s[i][k]) {has++;break;}
		if (same!=a[i]||has-same!=b[i]) return 0;
	}
	ans=x*1000+y*100+z*10+w;
	return 1;
}
signed main(){
	n=read();
	for (int i=1;i<=n;i++) cin>>s[i],a[i]=read(),b[i]=read();
	for (int x=0;x<=9;x++) for (int y=0;y<=9;y++) for (int z=0;z<=9;z++) for (int w=0;w<=9;w++) if (check(x,y,z,w)) cnt++;
	if (cnt==0) cout<<"Incorrect data";
	else if (cnt>1) cout<<"Need more data";
	else if (ans<1000) cout<<0<<ans;
	else cout<<ans;
	return 0;
}
```


---

## 作者：CEFqwq (赞：3)

本题是典型的暴力枚举，但坑点是真的多，防不胜防，建议评黄或绿。具体实现代码也有一点长，坑点如下：

1. 输出时不足四位要手动补 $0$，可以用 `printf` 格式化输出，但我开了 `cin/cout` 优化，只能加特判，强行判断位数。

2. 这个不应该说是坑点，但要看细节。这题感觉做法比较难，但看到数据范围在 $10^4$ 量级就可以想到暴力枚举。时间复杂度比较好算。最外层枚举 $10^4$ 个数（当然可以通过分析加以优化，其实只用枚举 $123$ 至 $9876$），然后枚举 $n$ 条条件，每条条件里要比对 $16$ 次（由于是 $4$ 位数，任意两位都要比对一次，就是 $16$ 次），也就是说可以把它看成 $O(n)$ 的，只不过要乘上一个 $1.6 \times 10^5$ 左右的常数，对于极小的 $n$，这个常数并不算大，极限大概就是枚举 $2 \times 10^6$ 次以内，但由于第 $3$ 条（见下），实际可能小于这个数值。

3. 由于不能有任意两位相同，分离每一位后要特判是否有两位相同，有就 `continue`。

这道题写起来不简单，有以下几个小技巧：

1. 对于每组输入，用结构体存储会更方便，不容易搞混。

2. 判断条件时，如果不成立，可以直接 `break`，这样可以减少一些枚举次数，也更容易理解。

3. 分离数位用循环更好想，只不过循环时用的数组记得初始化，否则会挂掉（开全局也行，但别忘了 `memset`）。

具体代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct num{
	public:
		int gus,ac,pc;
};//结构体存每组数据 
num a[105];
int mz[10001];//桶 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);//cin/cout优化，如果代码中同时要用cin和scanf、cout和printf就会导致错乱，出现无法预计的后果 
	cin>>n;
	for(register int i=0;i<n;i++)cin>>a[i].gus>>a[i].ac>>a[i].pc;
	for(register int i=0;i<=9999;i++){//枚举每个数，可以直接学习Alex_Wei大神的做法枚举 123~9876，有一定的优化 
		int p=0;
		for(register int j=0;j<n;j++){
			int aa[4]={},js1=0,b[4]={},js2=0;//记得清空 
			int qq=i,p1=0,p2=0;
			while(qq){
				aa[js1++]=qq%10;
				qq/=10;
			}//这一段可能较难理解，如果不是4位数，循环不会执行4次怎么办？这就要说到初始化了，初始化为0，自动加上前导零，不用逐位分离或特判了 
			if(aa[0]==aa[1]||aa[0]==aa[2]||aa[1]==aa[2]||aa[0]==aa[3]||aa[1]==aa[3]||aa[2]==aa[3])continue;//判断是否有重复 
			qq=a[j].gus;
			while(qq){
				b[js2++]=qq%10;
				qq/=10;
			}//逐位分离 
			for(register int k=0;k<4;k++)if(aa[k]==b[k])p1++;//枚举完全正确的数位 
			for(register int k=0;k<4;k++)
				for(register int l=0;l<4;l++)
					if(l!=k)if(aa[k]==b[l])p2++;//枚举存在但错位的数位 
			if(p1==a[j].ac&&p2==a[j].pc)p++;//满足一个条件 
			else break;//不符合要求，直接往下枚举 
		}
		if(p==n)mz[i]=1;//如果满足每个条件，说明这个数符合要求，这里用桶来存，其实可以数组+指针，速度更快 
	}
	int jishu=0,res=0;
	for(register int i=0;i<=9999;i++)if(mz[i]==1)jishu++,res=i;//枚举每一个数，如果有多个解，不必输出res，直接覆盖也行 
	if(jishu==0)cout<<"Incorrect data";//不存在一组解 
	else if(jishu==1){
		if(res<10)cout<<"000"<<res;
		else if(res<100)cout<<"00"<<res;
		else if(res<1000)cout<<"0"<<res;
		else cout<<res;//特判res是几位数，前两个特判可省略，为了更好理解写上 
	}
	else cout<<"Need more data";//存在多组解 
}
```

---

## 作者：御坂美琴0502 (赞：3)

## 暴力出奇迹

### 暴扫$0~9999$，看符合条件的数有几个。。。
### $<0$ 输出"Incorrect data"
### $=1$ 输出答案
### $>1$ 输出"Need more data"

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)

using namespace std;
long long n,a[11],b[11],c[11];
long long sum,ans,t[5];
long long tmp,tmp1,tmp2,tmp0;
inline long long read()
{
    long long x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
signed main()
{
    n=read();
    for(register long long i=1;i<=n;++i) a[i]=read(),b[i]=read(),c[i]=read();
    for(register long long i=0,flag;i<=9999;++i)
    {
        tmp=i,t[1]=tmp%10,tmp/=10,t[2]=tmp%10,tmp/=10,t[3]=tmp%10,tmp/=10,t[4]=tmp%10;
        if(t[1]==t[2]||t[1]==t[3]||t[1]==t[4]) continue;
        if(t[2]==t[3]||t[2]==t[4]) continue;
        if(t[3]==t[4]) continue;
        flag=1;
        for(register long long j=1;j<=n;++j)
        {
            tmp1=0,tmp2=0,tmp=(a[j]<<3)+(a[j]<<1);
            for(register long long k=1;k<=4;++k)
            {
                tmp/=10,tmp0=tmp%10,tmp1=tmp1+(t[k]==tmp0);
                for(register long long l=1;l<=4;++l)
                    tmp2=tmp2+((l==k)?0:(t[l]==tmp0));
            }
            if(tmp1!=b[j]||tmp2!=c[j]){flag=0;break;}
        }
        sum+=flag,ans=flag?i:ans;
    }
    if(!sum)  puts("Incorrect data");
    else if(sum==1) printf("%04lld\n",ans);
    else puts("Need more data");
}

```

---

## 作者：lzt415 (赞：1)

## 思路
本题不是很难，暴力即可，~~毕竟标签上都这么说了~~。

暴力枚举每一位，也就是 `guess` 函数的作用，可以根据容斥原理得知，排序后其相同位数就是各自拥有的相同位数减去相同位数，注意了，别忘了加上 $0$ 如果在答案小于 $1000$ 的时候。  
最后输出，按照题意要求分三种情况，所以还要一个计数器计算共有几种答案。

总复杂度完全可以通过本题。
## code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n, cnt;
int a[15], b[15];
int ans; 
char s[15][15];

bool guess(int q, int w, int e, int r) {
    int A[4] = {q, w, e, r};
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            if (A[i] == A[j])
            {
                return 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) 
	{
        int x = 0, y = 0;
        for (int j = 0; j < 4; j++)
        {
            if (A[j] + '0' == s[i][j])
            {
                y++;
            }
        }
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if (A[j] + '0' == s[i][k]) 
				{
                    x++;
                    break;
                }
            }
        }
        if (y != a[i] || x - y != b[i]) {
            return 0;
        }
    }
    ans = q * 1000 + w * 100 + e * 10 + r;
    return 1;
}

int main() 
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
		scanf("%s", s[i]);
		cin >> a[i] >> b[i];
	}
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            for (int k = 0; k <= 9; k++)
            {
                for (int l = 0; l <= 9; l++)
                {
                    if (guess(i, j, k, l))
                    {
                        cnt++;
                    }
                }
            }
        }
    }
    if (cnt==0)
    {
		cout<<"Incorrect data";
	}
    else if (cnt >= 2)
    {
    	cout<<"Need more data";
    }
    else 
	{
        if (ans < 1000)
        {
			cout<<0;
		}  
        cout << ans;
    }
    return 0;//很好理解，不必多言。
}
```

---

## 作者：2021changqing52 (赞：1)

# 思路：
### 暴力出奇迹！
当我们看到 $0\sim1000$ 的答案范围时，我们就可以想到枚举每个数字（毕竟只有 $10^4$），寻找相同和有但位置不正确的位置的个数（两重循环 $4\times4$），这样既不会 TLE，也不会让代码太过于复杂，~~真是两全其美~~。
# AC Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#pragma GCC optimize(3)
using namespace std;
ll n,a[11],b[11],c[11],sum;
ll ans,t[5],tmp,t1,t2,t3;
int main(){
	cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i]>>c[i];//存储输入（有点像离线） 
    for(int i=0,flag;i<=9999;i++){//暴力枚举 
        tmp=i;
		t[1]=tmp%10,tmp/=10;//算出各位 
		t[2]=tmp%10,tmp/=10;
		t[3]=tmp%10,tmp/=10;
		t[4]=tmp%10,tmp/=10;
        if(t[1]==t[2]||t[1]==t[3]||t[1]==t[4]||//判重 
		t[2]==t[3]||t[2]==t[4]||t[3]==t[4])continue;
        flag=1;
        for(int j=1;j<=n;j++){//判断 
            t1=0,t2=0,tmp=a[j]*10;
            for(int k=1;k<=4;k++){
                tmp/=10,t3=tmp%10,t1+=t[k]==t3;
                for(int l=1;l<=4;l++)t2+=l==k?0:t[l]==t3;
            }
            if(t1!=b[j]||t2!=c[j]){flag=0;break;}
        }
        sum+=flag;flag&&(ans=i);
    }
    if(!sum)puts("Incorrect data");//输出 
    else if(sum==1)printf("%04lld",ans);
    else puts("Need more data");
}
```

---

## 作者：long_long__int (赞：0)

感觉评蓝有点虚高啊。

# 题目解法

## 大致算法
一眼望去，一个 $1\le n\le10$ 赫然出现在眼前，于是我们就有了一个~~邪恶~~暴力的想法，枚举一下 $0\sim9999$ 的所有数，在判断一下是否符合题目要求，就能做出来了。

## 注意事项

- 如果位数不足四位要补零，不然就会像[这样](https://codeforces.com/problemset/submission/63/292737327)。

- 不要手打！如果打错就喜提挂分！

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int nm[15][5],b[15],c[15];
bool check(int x[]){
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(i==j) continue;
			if(x[i]==x[j]) return false;
		}
	}
	
	for(int s=1;s<=n;s++){
		
	int q=0;//数值，位置都对的数 
	for(int i=1;i<=4;i++){
		if(x[i]==nm[s][i]) q++;
	}
	if(q!=b[s]) return false;
	//-------
	int w=0;//有数值，但位置不对的书 
	
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(i==j) continue;
			if(x[i]==nm[s][j]) w++;
		}
	}
	if(w!=c[s]) return false;
	}
	return true;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		char ch;
		for(int j=1;j<=4;j++) cin>>ch,nm[i][j]=ch-'0';
		cin>>b[i]>>c[i];
	}
	int cnt=0,ans=0;
	int a[5];
	for(a[1]=0;a[1]<=9;a[1]++){
		for(a[2]=0;a[2]<=9;a[2]++){
			for(a[3]=0;a[3]<=9;a[3]++){
				for(a[4]=0;a[4]<=9;a[4]++){
					if(check(a)) cnt++,ans=a[1]*1000+a[2]*100+a[3]*10+a[4];
				}
			}
		}
	}
	if(cnt<=0) printf("Incorrect data");
	else if(cnt>1) printf("Need more data");
	else printf("%04d",ans);
	return 0;
}
```

[通过记录。](https://codeforces.com/problemset/submission/63/292737437)

---

## 作者：ZLCT (赞：0)

# CF63C Bulls and Cows
## 题目翻译
现在有一个各位不同的四位数（可能有前导 $0$），给定 $n$ 次已有询问，每次询问形如一个可能带前导 $0$ 的四位数。回答会给出有几个数值和位置都是对的，有几个数值出现了但是位置不对。问能否根据这 $n$ 次询问确定出一个唯一的四位数，若不能还需判断是有多组合法解还是没有合法解。
## solution
看到这是一个四位数，$n$ 又小于等于 $10$，于是就考虑直接暴力枚举每一个四位数并判断是否是一个合法解。\
那么下面我们一步步来考虑。\
首先是如何枚举带前导 $0$ 的四位数，在这里我们与其枚举 $0\sim 9999$ 的整数再补前导 $0$，不如直接枚举每一位的数字。这样还可以方便我们拆出每一位并判断是否有重复数字。\
接下来就是判断一个数是否是一个合法解，这一步的意思相当于对于 $n$ 组已有询问，当前枚举的数作为标准，是否得出来的 $n$ 组回答和输入回答一样。\
那对于每一组回答，我们分成数值和位置都对以及数值对位置不对两种情况。对于数值和位置都对的情况好判断，就是对应位置数字相同。\
那数值对了位置不对呢？\
由于数据范围实在太小了，我们可以直接拿两个 `set` 储存不满足数值和位置都对的条件的数字，那么我们只需要枚举输入数字里剩余的字符，判断当前枚举的字符里有没有剩下与之匹配的字符，有的话就把它删去以免影响下面判断。\
当然你也可以利用 `map`，取输入数字里每种数字与枚举数字出现次数的最小值。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
vector<string>ans;
struct node{
    string guess;
    int num1,num2;
}arr[11];
bool check(string s){
    for(int i=1;i<=n;++i){
        multiset<char>sst1,sst2;
        int correct1=0,correct2=0;
        for(int j=0;j<4;++j){
            if(s[j]==arr[i].guess[j])correct1++;
            else{
                sst1.insert(s[j]);
                sst2.insert(arr[i].guess[j]);
            }
        }
        for(char ch:sst2){
            if(sst1.count(ch)){
                correct2++;
                sst1.erase(sst1.lower_bound(ch));
            }
        }
        if(correct1!=arr[i].num1||correct2!=arr[i].num2)return 0;
    }
    return 1;
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>arr[i].guess>>arr[i].num1>>arr[i].num2;
    }
    for(char c1='0';c1<='9';++c1){
        for(char c2='0';c2<='9';++c2){
            for(char c3='0';c3<='9';++c3){
                for(char c4='0';c4<='9';++c4){
                    if(c1==c2||c2==c3||c3==c4||c1==c3||c1==c4||c2==c4)continue;
                    string ss="";
                    ss+=c1;ss+=c2;ss+=c3;ss+=c4;
                    if(check(ss))ans.push_back(ss);
                }
            }
        }
    }
    if(ans.empty())cout<<"Incorrect data\n";
    else if(ans.size()>1)cout<<"Need more data\n";
    else cout<<ans[0]<<'\n';
    return 0;
}
```

---

## 作者：kaaaai (赞：0)

## 分析

题意翻译已经很简洁了。
>$A$ 心里想一个 $4$ 位数，$B$ 每次猜一个数（必须各位都不相同且可以有前导 
$0$），$A$ 告诉他有猜的数有几个数字数值和位置都是对了，有几个数值出现了但是位置不对。$B$ 一共猜了 
$n$ 次（$n≤10$），问 $B$ 是否能猜出正确的数并输出，如果没有这样的数输出 “Incorrect data” 有多解输出 “Need more data”，有唯一解输出答案。

我们可以把 $B$ 猜的 $n$ 次及其结果视为对答案 $ans$ 的要求，求 $ans$ 的个数 $num$。

- 若 $num = 1$，输出 $ans$。
- 若 $num = 0$，输出无解。
- 若 $num > 1$，输出多解。

由于数据范围为 $n \le 10$ 且 $ans$ 为四位数，可以直接写一个暴力枚举算法。具体请看代码中的注释。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int num,corr,pcorr;
}s[15];//结构体数组存储B猜的四位数、数值和位置都对的数、数值对位置不对的数
int main(){
	int n,ans = 0;
	cin >> n;
	for(int i = 0;i < n;i++)cin >> s[i].num >> s[i].corr >> s[i].pcorr;//输入
	for(int i = 123;i <= 9876;i++){/枚举范围可以是123至9876
		int a[4];
		a[0] = i/1000,a[1] = i/100%10,a[2] = i/10%10,a[3] = i%10;//数组a存储i的四位数字
		if(a[0]==a[1]||a[0]==a[2]||a[0]==a[3]||a[1]==a[2]||a[1]==a[3]||a[2]==a[3])continue;//如果数字有重复就跳过
		for(int j = 0;j < n;j++){//遍历给出的n组要求
			int b[4],c = s[j].num,corrcnt = 0,pcorrcnt = 0;
        //后两个变量是计数器
			for(int k = 3;k >= 0;k--)b[k] = c%10,c/=10;//分解要求中四位数
			for(int k = 0;k < 4;k++){
				for(int l = 0;l < 4;l++){
					if(a[k]==b[l]){
						if(k==l)corrcnt++;
						else pcorrcnt++;
					}
				}
			}//遍历，计数
			if(!(corrcnt==s[j].corr&&pcorrcnt==s[j].pcorr))break;
        //如果本组要求不符合就break,枚举下一个i
			else if(j==n-1){//如果最后一组也通过
				if(ans==0)ans = i;//如果是第一个答案就赋值
				else{//否则是多组解
					cout << "Need more data";
					return 0;
				}
			}
		}
	}
	if(ans){//有解，此时是唯一解
		if(ans<1000)cout << 0 << ans;//注意输出前导0，WA on #34的是没有前导0
		else cout << ans;
	}
	else cout << "Incorrect data";//否则无解
	return 0;
}
```

建议评绿，~~因为本蒟蒻做出来了~~。

---

## 作者：AlicX (赞：0)

## Solution 

不难根据数据范围想出暴力枚举每一位的方法，当我们获得一个数 $x$ 时，只需要判断：

1. $x$ 的各位均不相同。

2. 枚举 $n$ 个限制条件，$O(1)$ 判断 $a_i$ 与 $x$ 有几个数字数值和位置都是对了的数量等于给定的，有几个数值出现了但是位置不对的数量等于给定的。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second 
#define il inline 
#define db double
#define low(x) x&-x 
#define pb(x) push_back(x) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=11,INF=1e9+7;  
int n; 
struct Mind{ 
	string x; 
	int w1,w2;  
	il bool operator<(Mind &Cyan)const{ } 
}ds[N];  
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il bool check(int A,int B,int C,int D){ 
	for(int i=1;i<=n;i++){ 
		int cnt1=0,cnt2=0; 
		int a=ds[i].x[0]-'0',b=ds[i].x[1]-'0',c=ds[i].x[2]-'0',d=ds[i].x[3]-'0'; 
		if(a==A) cnt1++; if(b==B) cnt1++; if(c==C) cnt1++; if(d==D) cnt1++; 
		if(a==B||a==C||a==D) cnt2++; if(b==A||b==C||b==D) cnt2++; 
		if(c==A||c==B||c==D) cnt2++; if(d==A||d==B||d==C) cnt2++;  
		if(cnt1!=ds[i].w1||cnt2!=ds[i].w2) return false; 
	} return true; 
} 
signed main(){ 
	n=read(); int ans=0,cnt=0; 
	for(int i=1;i<=n;i++) cin>>ds[i].x,ds[i].w1=read(),ds[i].w2=read(); 
	for(int a=0;a<=9;a++){ 
		for(int b=0;b<=9;b++){ 
			for(int c=0;c<=9;c++){ 
				for(int d=0;d<=9;d++){ 
					if(a==b||a==c||a==d||b==c||b==d||c==d) continue; 
					if(check(a,b,c,d)) ans=a*1000+b*100+c*10+d,cnt++; 
				} 
			} 
		} 
	} if(!cnt) puts("Incorrect data"); 
	else if(cnt==1){ 
		if(ans<1000) cout<<0; 
		if(ans<100) cout<<0; if(ans<10) cout<<0; 
		cout<<ans<<endl; 
	} else puts("Need more data"); 
	return 0; 
} /* */ 
```



---

