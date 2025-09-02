# Vasya and Football

## 题目描述

Vasya has started watching football games. He has learned that for some fouls the players receive yellow cards, and for some fouls they receive red cards. A player who receives the second yellow card automatically receives a red card.

Vasya is watching a recorded football match now and makes notes of all the fouls that he would give a card for. Help Vasya determine all the moments in time when players would be given red cards if Vasya were the judge. For each player, Vasya wants to know only the first moment of time when he would receive a red card from Vasya.

## 样例 #1

### 输入

```
MC
CSKA
9
28 a 3 y
62 h 25 y
66 h 42 y
70 h 25 y
77 a 4 y
79 a 25 y
82 h 42 r
89 h 16 y
90 a 13 r
```

### 输出

```
MC 25 70
MC 42 82
CSKA 13 90
```

# 题解

## 作者：LegendaryGrandmaster (赞：3)

简单模拟。

我们可以把黄牌记为犯规 $1$ 次，红牌记为犯规 $2$ 次，只要选手累计的犯规次数 $\ge 2$，我们就依次输出这名选手的队伍、编号与时间。

我们可以拿 map 存储不同队伍的成员的犯规次数。只要这名成员犯规次数 $\ge 2$ 了，我们就可以把这名成员记为 $1$，以后如果遇到就跳过。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int t,x;
	char op,c;
}a[101];
map<int,map<int,int> >mp,ok;
int main()
{
	string s1,s2;
	cin>>s1>>s2;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].t>>a[i].op>>a[i].x>>a[i].c;
		if(a[i].c=='y')mp[a[i].op][a[i].x]++;
		else mp[a[i].op][a[i].x]+=2;
		if(!ok[a[i].op][a[i].x]&&mp[a[i].op][a[i].x]>=2){
			cout<<(a[i].op=='h'?s1:s2)<<' '<<a[i].x<<' '<<a[i].t<<'\n';
			ok[a[i].op][a[i].x]=1;
		}
	}
}
```

---

## 作者：DeepSkyBlue__ (赞：1)

这题要我们求出各个球员被罚下的时间且要按时间顺序输出，两张黄牌转化为一张红牌。那么我们一边读入一边输出。

用两个数组分别储存主队和客队各个球员被警告的情况，黄牌就加 $1$ ，红牌就加 $2$ ，如果这个人被罚下了就修改成 `INT_MIN` ，这个人以后的输入数据就不会处理了。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100001],b[100001];//记录球员被黄牌/红牌的情况
int main()
{
    string s1,s2;
	cin>>s1>>s2;//球队名字
	int n;
	cin>>n;
	while(n--)
	{
		int T,num;
		char c,d;
		cin>>T>>c>>num>>d;
		if(c=='h')//主队球员
		{
			if(d=='y')a[num]++;//黄牌
			else a[num]+=2;//红牌
			if(a[num]>=2)//被罚下了
			{
				a[num]=INT_MIN;
				cout<<s1<<" "<<num<<" "<<T<<endl;//输出球队名，号码和下场时间
			}
		}
		else//客队球员
		{
			if(d=='y')b[num]++;//黄牌
			else b[num]+=2;//红牌
			if(b[num]>=2)
			{
				b[num]=INT_MIN;
				cout<<s2<<" "<<num<<" "<<T<<endl;//输出球队名，号码和下场时间
			}
		}
	} 
	return 0;
}
```


---

## 作者：tommyfj (赞：0)

~~一道简单的模拟题~~

讲一下我的做法：

1. 出现一张红牌或两张黄牌时，把该球员做标记，并输出该球员所在的队伍、球员编号以及时间。

从代码中可见，我是分别用 $d_1$ 数组和 $d_2$ 数组对被罚下的球员进行标记。（$d_1$ 数组标记第一支队伍被罚下的球员，$d_2$ 数组标记第二支队伍被罚下的球员）

然后，$d_1y$ 数组是用来记第一支队伍中每个球员的黄牌数量，$d_2y$ 数组是用来记第二支队伍中每个球员的黄牌数量。

Code:

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n;
int d1[101], d2[101], d1y[101], d2y[101];
string s1, s2;
int main()
{
    cin >> s1 >> s2;
    scanf("%d",&n);
    while (n --)
    {
        char c, p;
        int t, h;
        cin >> t >> c >> h >> p;
        if ((!d1[h] || !d2[h]) && p == 'r')//当牌子时红牌时，判断该球员是否已经被罚下。
        {
            if (!d1[h] && c == 'h')//如果他是队伍 1 的球员且没被罚下，则输出
            {
                d1[h] = 1;
                cout << s1 << " " << h << " " << t << endl;
            }
            else if (!d2[h] && c == 'a')//如果他是队伍 2 的球员且没被罚下，则输出
            {
                d2[h] = 1;
                cout << s2 << " " << h << " " << t << endl;
            }
        }
        else if ((!d1[h] || !d2[h]) && p == 'y')//当牌子时黄牌时，判断该球员是否已经被罚下。
        {
            if (!d1[h] && c == 'h')//如果他是队伍 1 的球员且没被罚下，则继续
            {
                d1y[h] ++;
                if (d1y[h] == 2)//若有两张黄牌了，则该球员被罚下，然后输出
                {
                    cout << s1 << " " << h << " " << t << endl;
                    d1[h] = 1;
                }
            }
            else if (!d2[h] && c == 'a')//如果他是队伍 2 的球员且没被罚下，则继续
            {
                d2y[h] ++;
                if (d2y[h] == 2)//若有两张黄牌了，则该球员被罚下，然后输出
                {
                    cout << s2 << " " << h << " " << t << endl;
                    d2[h] = 1;
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有两个球队在踢足球，现在给出一些足球运动员被黄牌或红牌警告的时间，求每个队员第一次被红牌警告的时间。

注意：根据足球比赛规则，**两张黄牌自动换成一张红牌**。

**数据范围：比赛时间 $90$ 分钟，足球员号码 $\leqslant 99$。**
## Solution
这道题目就是一个很纯粹的模拟。主要注意以下几点：

1. 两个球队当中也许有相同号码的球员。比如说近现代的 $10$ 号球员有很多，比如说齐达内和梅西等。
2. 球员被红牌下场了，但后面还有可能会录入关于该球员的警告信息，此时应该忽略它。

考虑完这些，模拟就简单多了。
## Code
```cpp
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

string a, b;
int num_of_foul, ye[2][1007], vis[2][1007];

int main() {
	cin >> a >> b;
	scanf("%d", &num_of_foul);
	for(int i = 1; i <= num_of_foul; ++i) {
		int t_of_foul, num;
		char ha[2], yr[2];
		scanf("%d%s%d%s", &t_of_foul, ha, &num, yr);
		if(yr[0] == 'r' && (ha[0] == 'h' ? !vis[0][num] : !vis[1][num])){
			if(ha[0] == 'h')	cout << a << ' ';
			else if(ha[0] == 'a')	cout << b << ' ';
			printf("%d %d\n", num, t_of_foul);
			if(ha[0] == 'h')	vis[0][num] = 1;
			else if(ha[0] == 'a')	vis[1][num] = 1;
		} else if(yr[0] == 'y') {
			if(ha[0] == 'h')	ye[0][num]++;
			else if(ha[0] == 'a')	ye[1][num]++;
			if(ye[0][num] == 2 && !vis[0][num]) {
				cout << a << ' ';
				printf("%d %d\n", num, t_of_foul);
				vis[0][num] = 1;
			} else if(ye[1][num] == 2 && !vis[1][num]){
				cout << b << ' ';
				printf("%d %d\n", num, t_of_foul);
				vis[1][num] = 1;
			}
		}
	}
} 
```

---

## 作者：引领天下 (赞：0)

这题其实就是模拟

题目大意：已知有两个球队home和away，现在给出一些足球运动员被黄牌或红牌警告的时间，求每个队员第一次被红牌警告的时间。（2张黄牌会自动变成1张红牌）

已经描述的很清楚了。

具体看代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=111;
int n,f[2][max_n];
string a[2];
int main(){
    cin>>a[0]>>a[1]>>n;//读入2个队的名字和总被罚次数
    while(n--){
        int t,num,q,c;
        char c1,c2;
        cin>>t>>c1>>num>>c2;//读入被罚的队、队员编号、红牌还是黄牌和时间
        if(c1=='h')q=0;
        else q=1;//q=0->home队
        if(c2=='y')c=1;
        else c=2;//保证一张红牌抵两张红牌
        if(f[q][num]<2){//如果之前没被罚下去
            f[q][num]+=c;//加上本次的惩罚
            if(f[q][num]>=2)cout<<a[q]<<" "<<num<<" "<<t<<endl;//如果本次被罚到红牌了，再见
        }
    }
    return 0;
}
```

---

## 作者：jimmyfj (赞：0)

这题只需要判断每一次的警告是红牌还是黄牌，并且是否有红牌或者黄牌的数量是否达到 $2$ 张，就可以断定是否要被红牌警告。

**注意：只要是被红牌警告过后，即使后面再被红牌警告，也只须输出一次就可以了，不用在输出一次。（被红牌警告的要求是：一张红牌或者两张黄牌）**

本人用 map 分别统计每个队伍的每个队员相应的黄牌数量，记为 $p,g$，以及标记两队伍的每个成员是否已被红牌警告过，记为 $vis1,vis2$。

**温馨提示：** 如果一个队伍的队员拿到了红牌，不用去记该队员的红牌数，只用判断是否已被红牌警告过就可以了，反之黄牌要计数，并判断是否已被红牌警告过。

参考代码 ：
```cpp
#include <bits/stdc++.h>

using namespace std;

map<int, int> p;//home队员的黄牌个数
map<int, int> g;//away队员的黄牌个数
map<int, bool> vis1;//home队员是否已被红牌警告过
map<int, bool> vis2;//away队员是否已被红牌警告过

string home, away;
int n;
int number, times;
char card, team;

int main () {
    cin >> home >> away;
    scanf("%d", &n);
    while (n --) {
        cin >> times >> team >> number >> card;
        if (team == 'h') {
            if (card == 'r' && vis1[number] == false) {//是否有了红牌且未被红牌警告
                cout << home << " " << number << " " << times << "\n";
                vis1[number] = true;//标记为警告过了
            } else {
                p[number] += 1;
                if (p[number] == 2 && vis1[number] == false) {//是否由了两张黄牌且为被红牌警告
                    cout << home << " " << number << " " << times << "\n";
                    vis1[number] = true;//同样的，标记为警告过了
                }
            }
        } else {//以下同上面的一样，只是队伍不一样
            if (card == 'r' && vis2[number] == false) {
                cout << away << " " << number << " " << times << "\n";
                vis2[number] = true;
            } else {
                g[number] += 1;
                if (g[number] == 2 && vis2[number] == false) {
                    cout << away << " " << number << " " << times << "\n";
                    vis2[number] = true;
                }
            }
        }
    }
    
    return 0;
}
```


---

