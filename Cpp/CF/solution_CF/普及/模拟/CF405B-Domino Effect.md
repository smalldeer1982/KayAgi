# Domino Effect

## 题目描述

小克里斯认为**简单地推倒**多米诺骨牌没有意思，他认为这太随意了，不需要技巧。因此，他决定玩~~一种他歪歪出来的~~多米诺骨牌游戏并进行“多米诺骨牌表演”。

克里斯把 $n$ 张多米诺骨牌排在一条线上，垂直竖立。一开始，他**同时**将一些多米诺骨牌推向左侧或右侧，并且保证，在每两个多米诺骨牌推向相同方向之间的某个地方，至少有一个多米诺骨牌被推向相反的方向。

每一秒，每个倒在左边的多米诺骨牌将会推动左边相邻的多米诺骨牌。同样地，向右倾斜的多米诺骨牌将会推动右边相邻的多米诺骨牌。当一个垂直的多米诺骨牌有从两边落下的多米诺骨牌时，由于力量的平衡而保持不变。以下这张图（包括3个例子）显示了该过程的一个可能示例。

![](https://cdn.luogu.org/upload/vjudge_pic/CF405B/37fecb2c12dba94b96d336756a84bf7894c6655a.png)

给出克里斯推动多米诺骨牌的最初方向，请编程找到在过程结束时垂直留下的多米诺骨牌的数量。

## 样例 #1

### 输入

```
14
.L.R...LR..L..
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
R....
```

### 输出

```
0
```

## 样例 #3

### 输入

```
1
.
```

### 输出

```
1
```

# 题解

## 作者：DarkShadow (赞：4)

# CF405B（模拟）

## 题目大意：

给出 $N$ 个多米诺骨牌，同时推动一些骨牌，求最后有多少个骨牌保持竖立。

## 思路分析：

我们可以分情况讨论骨牌竖立的情况。

1. 骨牌左右都没有倒下的骨牌。
2. 骨牌左右倒下的骨牌数量相等。

我们可以从左往右扫一遍，记录前面有多少个骨牌没有被推动。

如果当前骨牌也没有被推动，那么我们把计数器加一；

如果当前骨牌被推动了，那么我们再分情况讨论：

1. 当前骨牌向右推动，前面的骨牌没有倒下时，我们把答案直接加上计数器；

2. 当前骨牌向左推动，前面有骨牌向右推动，那么我们判断计数器是否为奇数，如果是就把答案加一；

3. 对于其他情况，都不会影响答案。

按照这样的方式扫一遍就可以得到答案。

**注意：如果最后的几个骨牌没有被推动，仍然需要记算答案。**

## 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3005;
int n,d[N],ans,dir,cnt;
int main(){
	char c;
	scanf("%d\n",&n);
	for(int i=1;i<=n;i++){
		scanf("%c",&c);
		if(c=='L')  d[i]=-1;//-1表示向左推，1表示向右推
		if(c=='R')  d[i]=1;
	}
	dir=-1;
	for(int i=1;i<=n;i++){
		if(d[i]==0)  cnt++;//第一种情况
		else if(d[i]==-1&&dir==1)  ans+=cnt%2;//第二种情况
		else if(d[i]==1&&dir==-1)  ans+=cnt;//第三种情况
		if(d[i]!=0)  cnt=0,dir=d[i];
	}
	if(dir==-1)  ans+=cnt;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Jerrlee✅ (赞：4)

## 题意
给你一些多米诺骨牌，现在将他们向左或向右推，并且保证，**在每两个多米诺骨牌推向相同方向之间的某个地方，至少有一个多米诺骨牌被推向相反的方向**。

可以看此图理解样例一：

![](https://cdn.luogu.org/upload/vjudge_pic/CF405B/37fecb2c12dba94b96d336756a84bf7894c6655a.png)

橙色的是站着的（共 $4$ 个）。
## 思路
有三种情况可能会让骨牌站着：

1. 最左边有骨牌且没别的骨牌推它；

2. 最右边有骨牌且没别的骨牌推它；

3. 向右的力和向左的力间有奇数个骨牌。

注意一下，`L` 和 `R` 也是骨牌，一样会倒。

按照上面的思路，可以写出如下代码：
```cpp
#include<iostream>
using namespace std;
int cnt,n,ans,flag;
string s;
int main(){
    cin>>n>>s;
    for(int i=0;i<n;i++){
        if(flag){
			if(s[i]=='.') cnt++;
			else{
				ans+=(cnt%2);
				cnt=0,flag--;
			}
		}
        else{
            if(s[i]=='.') cnt++;
			else{
				if(s[i]!='L') ans+=cnt,flag++;
				cnt=0;
			}
		} 
    }
    cout<<ans;
}
```
然后就会发现样例 $2$ 都没过。

这时候就提醒了我们要特判，$flag$ 依旧为 $0$ 就说明向左或向右的力没有另一股力阻挡它。

加上如下代码：`if(!flag) ans+=cnt;`

即可 AC！

[AC 记录（洛谷）](https://www.luogu.com.cn/record/69721836)

[AC 记录（CF）](https://codeforces.com/contest/405/submission/146987365)

---

## 作者：BZHZS (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/CF405B)

通过读题， 我们可以相邻的向左推和向右推之间的多米诺骨牌看为一个区域， 操作过后所有的多米诺骨牌分成了若干个区域，如图所示这一排多米诺骨牌被分为了$3$个区域。![](https://z3.ax1x.com/2021/09/30/4oyoff.png)

我们可以发现一些规律
1. 不属于任何区域的多米诺骨牌一定不会倒塌。
2. 如果第 $1$ 个区域的开头是第一个多米诺骨牌， 那么这个区域的所有多米诺骨牌都会倒塌
3. 除了第 $1$ 个区域外， 如果这一个区域有奇数个多米诺骨牌， 就会有 $1$ 个多米诺骨牌不会倒塌，否则所有多米诺骨牌都会倒塌。

然后我们就可以开始模拟了。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node {
	char a;
	int id;
};

const int N = 3010;

node a[N];
string ss;
int s, ans, cnt, now;

int main() {
	cin >> s >> ss;

	for (int i=0; ss[i]!='\0'; i++) {
		if (ss[i] == 'L') {a[++cnt].a = 'L'; a[cnt].id = i+1;}
		if (ss[i] == 'R') {a[++cnt].a = 'R'; a[cnt].id = i+1;}
	}

	for (int i=1; i<=cnt; i++) {//枚举每一个区域
		if (a[i].a == 'R') ans += a[i].id-now-1;//两个区域之间的多米诺骨牌肯定不会倒塌
		else if ((a[i].id-now-1)%2==1 && now!=0) ans++;//若区域内有奇数个多米诺骨牌， 就有一个不会倒塌，并特判开头是否为第1个多米诺骨牌
		now = a[i].id;//记录枚举位置
	}
	if (a[cnt].a == 'L') ans += s - a[cnt].id;//加上最右边没有枚举到的不属于任何区域的多米诺骨牌
	if (cnt == 0) cout << ss.size() << endl;//特判：如果没有操作，则所有多米诺骨牌都不会倒塌
	else cout << ans << endl;

	return 0;
}
```


---

## 作者：Tune_ (赞：2)

这道题其实就是模拟鸭~

从左到有遍历，记录初始值为'.'的数量，如果碰到一个‘L’，直接清零，如果碰到‘R’，ans直接加，并记录下R。
找下一个‘L’，如果两个之间相差的牌的数量为奇数，倒完后必定中间一个立着，ans++就OK啦。

不过需要注意的是，最后可能还有没碰过的，要加上。

附上AC代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,ans=0,cnt=0,t=1;
char lr,bj;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>lr;
		if(lr=='.')//初始是直的，计数++
			cnt++;
		else
		{
			if(lr=='R'&&bj!='R')//右，标记为上一个动的方向
				ans+=cnt;
			if(lr=='L'&&bj=='R')//左
				if(cnt%2==1)
					ans++;
			cnt=0;
			bj=lr;//记录
		}
	}
	if(cnt&&bj!='R')//最后还有
		ans+=cnt;
	cout<<ans;
	return 0;//拜了个拜~
}
```
走过路过，给本蒟蒻点个赞吧~

---

## 作者：Beacon_wolf (赞：1)

## 题目思路
我们可以想到有两种情况下骨牌会立着：

- 两边没有骨牌倒向自己；
- 两边倒向自己的骨牌相同。

对于每个没有左右操作的骨牌，扫一遍它的左右方向，判断是否出现以上两种情况即可。
## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 3010;
int n;
int main(){
	cin >> n;
	string s;
	cin >> s;
	int ans = 0;
	for(int i = 0;i < n;i++){
		if(s[i] == '.'){
			int l = 0,r = 0;
			for(int j = i - 1;j >= 0;j--){
				if(s[j] == 'R'){
					l = abs(j - i);
					break;
				}else if(s[j] == 'L') break;
			}
			for(int j = i + 1;j < n;j++){
				if(s[j] == 'L'){
					r = abs(j - i);
					break;
				}else if(s[j] == 'R') break;
			}
			if(l == r){
				ans++;
				//cout << i << endl;
			}
		}
	}
	cout << ans << endl;
    return 0;
}

```

---

## 作者：yangdezuo (赞：0)

## 思路
这其实是一道水题，用模拟的方法，统计有多少倒掉了，最后用总数减掉就是答案了。
### 样例
![](https://cdn.luogu.com.cn/upload/image_hosting/qfav1t8k.png)

首先，先看第1、3、4个橙色骨牌，它们是因为左右都没有向它们倒，所以他们还是立着。

其次，第2个橙色骨牌，他是在左右两边倒了的中间正好被夹住，不同于第4堆（倒在一起的），第3堆，也就是第2个橙色骨牌这堆，它们的个数是奇数个，所以总有一个“夹缝生存”，偶数个则不会。

### 结论
按照以上方式，就可以统计出有多少倒掉了，最后用总数减掉就是答案了。

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
int n,t,k;//t用来统计倒掉的个数 k用来统计左右标志中间的个数 
string s;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>s;//读入 
	for(int i=0;i<n;i++)
		if(s[i]=='L'){ 
			for(int j=i;j>=0;j--)//向左 
				if(s[j]=='R') break;//遇到向右退掉 
				else if(j==0) t+=i+1;//统计从左到底 
		}
		else if(s[i]=='R'){
			for(int j=i;j<n;j++)//向右 
				if(s[j]=='L'){//遇到向左 
					k=j-i-1;
					if(k%2==1) t+=k+1;//中间的不倒 
					else t+=k+2;//中间的倒掉 
					break;//退掉 
				}
				else if(j==n-1) t+=n-i;//到底 
		}
	cout<<n-t;//输出
  return 0；//谢幕撒花
}
/*
14
.L.R...LR..L..
*/
```

---

## 作者：fwtv_24 (赞：0)

## 简单分析~~~

根据样例一的图示，很容易就能想到使用**模拟**来做此题。

### 那么我们就来分析多米诺骨牌站立时的两种情况：

1. 没有被其它牌推动的骨牌（如样例中的第          $1,3,4 $ 个橙色骨牌）

2. 被夹在两个向中间靠拢的骨牌推动且**两骨牌之间的距离为奇数**的一段骨牌中**最中间**的一块（如样例图片中的第二个橙色骨牌）

![样例1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF405B/37fecb2c12dba94b96d336756a84bf7894c6655a.png)


那么我们只需要针对以上两种情况分类讨论即可

我们可以先对整个字符串进行遍历，在发现字符 'L' 或  'R'  时进行判断。

但为避免情况一的左右两次分别遍历重复，我们对左右的遍历仅需一次的分类讨论，剩下的情况可以直接跳过。

多余的不用再讲了，注释在代码里。

## CODE
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans=0;
string s;
signed main()
{
	cin>>n;
	cin>>s;
	for(int i=0;i<n;i++)//对字符串进行遍历
	{
		if(s[i]=='L')//找出字符 'L' 或 'R'
		{
			for(int j=i;j>=0;j--)//对当前的 'L' 进行反向遍历
			{
				if(s[j]=='R')//找到与之相对的 'R' 字符
				{
					break;//避免操作重复
				}
				else if(j==0)//若没有 'R' 字符与之匹配
				{
					ans+=i-j+1;// ans 表示被推倒的牌数
				}
			}
		}
		if(s[i]=='R')
		{
			for(int j=i;j<n;j++)
			{
				if(s[j]=='L')//如果找到与 'R' 字符相匹配的 'L' 字符
				{
					int d=j-i-1;// LR 之间的距离（不含 L,R ）
					if(d%2==1) ans+=d+1;//如果是奇数，则被推倒数量为 d+1
					else ans+=d+2;//若是偶数，则被推倒数量为 d+2
					break;
				}
				else if(j==n-1)//如果没有与之相匹配的 'L' 字符
				{
					ans+=n-i;//被推倒的数量为 n-i
				}	
			}
		}
	}
	cout<<n-ans;//n-ans 为不倒的骨牌数量
	return 0;//养成好习惯！
}

```

---

## 作者：Tachibana27 (赞：0)

最后的骨牌竖着的仅有 $2$ 种情况：

1. 没有受到任何推动的力。

2. 受到的力被抵消且个数为**奇数**。

注意到：

>并且保证，在每两个多米诺骨牌推向相同方向之间的某个地方，至少有一个多米诺骨牌被推向相反的方向。

我们将一段左力和右力视为一段区间（最开始的和最末尾的也算一段区间），那么统计这一段内没有被推动的个数，如果为奇数答案加一即可。

code:

```cpp
int n;
std::string s;
bool rt;//向右的力，区间的左端点
int up;
int ans;
int main(){
	std::cin>>n>>s;
	s=" "+s;
	for(int i=1;i<=n;i++)
		if(rt)//如果有向右的力
			if(s[i]=='.')//若当前是一块骨牌
				up++;
			else{//必然是一个左力
				ans+=(up&1);//如果是奇数块
				up=0;
				rt=false;//此区间结束
			}
		else//没有向右的力，需要统计情况1或者新开一个区间
			if(s[i]=='.')//同上
				up++;
			else{
				if(s[i]=='R'){//若为向右的力，则up内是情况1
					ans+=up;
					rt=true;
				}
				up=0;
			}
	if(not rt)//最后一个区间，需要特殊处理
		ans+=up;
	std::cout<<ans;
	return 0;//撒花
}
```

---

## 作者：whyl (赞：0)

~~由我来补一篇题解~~
这道题就是一个模拟。
因为没有方法确定R做出的贡献
就把R打一个标记
注意看一下是否要中间的恢复即可
```c
#include<bits/stdc++.h>

using namespace std;

const int maxn=3005;

int n,a[maxn],v[maxn],last;

int main(){
    cin>>n;
    int len=0;
    while(1){
        char p=getchar();
        while(p!='.'&&p!='L'&&p!='R') p=getchar();
        if(p=='.') a[++len]=1;
        if(p=='L') a[++len]=2;
        if(p=='R') a[++len]=3;
        if(len==n) break;
    }
    last=1;
    for(int i=1;i<=n;i++){
        if(a[i]==3) {
            last=i;
            continue;
        }
        if(a[i]==2){
            for(int j=last;j<=i;j++) v[j]=1;
            if(last!=1||a[1]==3) if(((i-last)&1)==0) v[(last+((i-last)>>1))]=0;
            last=i+1;
        }
    }
    for(int i=n;i>=1;i--){
        if(a[i]!=1){
            if(a[i]==3) for(int j=i;j<=n;j++) v[j]=1;
            break;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++) ans+=(v[i]==0);
    cout<<ans<<endl;
    return 0;
}
```


---

