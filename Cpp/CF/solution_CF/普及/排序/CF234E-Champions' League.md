# Champions' League

## 题目描述

In the autumn of this year, two Russian teams came into the group stage of the most prestigious football club competition in the world — the UEFA Champions League. Now, these teams have already started to play in the group stage and are fighting for advancing to the playoffs. In this problem we are interested in the draw stage, the process of sorting teams into groups.

The process of the draw goes as follows (the rules that are described in this problem, are somehow simplified compared to the real life). Suppose $ n $ teams will take part in the group stage ( $ n $ is divisible by four). The teams should be divided into groups of four. Let's denote the number of groups as $ m $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/65e4300bd0cdae46f7d260b1389d3b214f9ce521.png)). Each team has a rating — an integer characterizing the team's previous achievements. The teams are sorted by the rating's decreasing (no two teams have the same rating).

After that four "baskets" are formed, each of which will contain $ m $ teams: the first $ m $ teams with the highest rating go to the first basket, the following $ m $ teams go to the second one, and so on.

Then the following procedure repeats $ m-1 $ times. A team is randomly taken from each basket, first from the first basket, then from the second, then from the third, and at last, from the fourth. The taken teams form another group. After that, they are removed from their baskets.

The four teams remaining in the baskets after $ (m-1) $ such procedures are performed, form the last group.

In the real draw the random selection of teams from the basket is performed by people — as a rule, the well-known players of the past. As we have none, we will use a random number generator, which is constructed as follows. Its parameters are four positive integers $ x,a,b,c $ . Every time there is a call to the random number generator, it produces the following actions:

- calculates ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/2fe2894178b5b7478ae2269aae243e7c851b6173.png);
- replaces parameter $ x $ by value $ y $ (assigns ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/72e8070934423a6837039e7a1e2f312765ec26ab.png));
- returns $ x $ as another random number.

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) means taking the remainder after division: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/c19545677f47a50d181dd7b00e822282597427db.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/770f8dc8f9b95dc42d2401b09019f707ad7418fc.png).

A random number generator will be used in the draw as follows: each time we need to randomly choose a team from the basket, it will generate a random number $ k $ . The teams that yet remain in the basket are considered numbered with consecutive integers from $ 0 $ to $ s-1 $ , in the order of decreasing rating, where $ s $ is the current size of the basket. Then a team number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/65912cf5ed5c94787700c166a6eeb79e0114a14b.png) is taken from the basket.

Given a list of teams and the parameters of the random number generator, determine the result of the draw.

## 说明/提示

In the given sample the random number generator will be executed four times:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/fe99c797dbb307d601e0f59e424f6250c45a7d38.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/baa288fe7b8d960b815b5367ff1126e08e6c706b.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/81b191782fc61308d51cf88ac0aba6c561fc0212.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/549ef2ab2cbb05e99d689f6ca803b6fab657873d.png).

## 样例 #1

### 输入

```
8
1 3 1 7
Barcelona 158
Milan 90
Spartak 46
Anderlecht 48
Celtic 32
Benfica 87
Zenit 79
Malaga 16
```

### 输出

```
Group A:
Barcelona
Benfica
Spartak
Celtic
Group B:
Milan
Zenit
Anderlecht
Malaga
```

# 题解

## 作者：Walter_Fang (赞：4)

### 大致题意

共有 $n$ 个人，每个人拥有各自的名字和积分，并给出一个随机数算法，将他们平均分成 $ \frac{n}{4}$ 组。

随机数公式：$x=(x\times a+b)\mod{c}$

### 解析

纯模拟，根据题意做。既然每个队伍都有各自的名字和积分，那么不妨使用结构体进行存储，然后根据积分从大到小排序。

排完序后用嵌套循环遍历每个分组中的每个队伍，使用题目中给出的公式产生随机数，用 `f` 数组记录该队伍是否已经被分组。**如果现在的人数等于产生的随机数，则循环次数就是需要的编号**，进行输出。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,q1,q2,q3,i,j,k,s,m,f[110];
struct no {
	int x;
	string y;
} a[110];
bool cmp(no l,no r) {
	return l.x>r.x;
}
int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>x>>q1>>q2>>q3;
	for(i=1; i<=n; i++)cin>>a[i].y>>a[i].x;
	sort(a+1,a+n+1,cmp);
	for(i=1; i<=n/4; i++) {
		cout<<"Group "<<char('A'+i-1)<<":"<<'\n';
		for(j=1; j<=4; j++) {
			x=(x*q1+q2)%q3;
			k=0;
			s=(j-1)*n/4+1;
			m=x%(n/4-i+1);
			while(1) {
				if(!f[s]) {
					k++;
					if(k==m+1)break;
				}
				s++;
			}
			f[s]=1;
			cout<<a[s].y<<'\n';
		}
	}
}
```

---

## 作者：封禁用户 (赞：3)

## 题意：         
有 $n$ 个人。每个人有他们的名字和积分，给出一个随机数算法，要把他们分成  $\dfrac{n}{4}$ 个组。             
生成随机数公式： $x=(x×a+b)$ $\bmod $ $ c$     

---------------
注意：本题的翻译有一个地方没有进行翻译，可能会影响大家理解：         
真正分组的条件是：抽取编号为 $k \bmod  s$ 的球队。          
其中 $k$ 代表的是生成的随机数。      
其中 $s$ 代表的是此个等级剩下的没有分组的人数。
## 分析
按题意一步步模拟，一共模拟 $\dfrac{n}{4}$ 次。        
模拟中，外层表示每个小组，内层表示每个等级。           
我们可以使用一个 ```len``` 数组来存储每个等级剩下的人数。           
找到以后就可以直接输出。         
细节很难调，请大家多加注意。         
还有，别忘了文件输入输出。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f,g,x1,a1,b1,c1,k;
int s1[100000],s2[100000],s3[100000],s4[100000],lss[1000000],len[50];
string s,ss[11451];
string zm[60]={"S","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};//用来输出Group
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>a;
	cin>>x1>>a1>>b1>>c1;
	for(int i=1;i<=a;i++){
		cin>>ss[i];
		cin>>lss[i];
	}
    //排序
	for(int i=1;i<=a;i++){
		for(int j=1;j<=a;j++){
			if(lss[i]<lss[j]){
				swap(lss[i],lss[j]);
				swap(ss[i],ss[j]);
			}
		}
	}
    //分为四个等级
	for(int i=1;i<=4;i++){
		for(int j=1;j<=a/4;j++){
			if(i==1){
				s4[j]=j;
				len[4]++;
			}
			if(i==2){
				s3[j]=a/4+j;
				len[3]++;
			}
			if(i==3){
				s2[j]=a/2+j;
				len[2]++;
			}
			if(i==4){
				s1[j]=a/4*3+j;
				len[1]++;
			}
		}
	}
    //模拟
	for(int j=1;j<=a/4;j++){
		cout<<"Group "<<zm[j]<<":"<<endl;
		for(int i=1;i<=4;i++){
			k=(x1*a1+b1)%c1;//生成随机数公式
			x1=k;
			if(i==1){
				k%=len[1];
				k++;
				for(int i=a/4;i>=1;i--){
					if(s1[i]!=-1){
						k--;
						if(k==0){
							cout<<ss[s1[i]]<<endl;
							len[1]--;
							s1[i]=-1;
						}
					}
				}
			}
			if(i==2){
				k%=len[2];
				k++;
				for(int i=a/4;i>=1;i--){
					if(s2[i]!=-1){
						k--;
						if(k==0){
							cout<<ss[s2[i]]<<endl;
							len[2]--;
							s2[i]=-1;
						}
					}
				}
			}
			if(i==3){
				k%=len[3];
				k++;
				for(int i=a/4;i>=1;i--){
					//cout<<"**";
					if(s3[i]!=-1){
						k--;
						if(k==0){
							cout<<ss[s3[i]]<<endl;
							len[3]--;
							s3[i]=-1;
						}
					}
				}
			}
			if(i==4){
				k%=len[4];
				k++;
				for(int i=a/4;i>=1;i--){
					if(s4[i]!=-1){
						k--;
						if(k==0){
							cout<<ss[s4[i]]<<endl;
							len[4]--;
							s4[i]=-1;
						}
					}
				}
			}
		}
	}
	return 0; 
} 
```
管理大大过一下吧，谢谢啊~

---

## 作者：封禁用户 (赞：2)

## CF234E Champions' League 题解

### 解题思路

这道题的思路非常简单，直接按题意**模拟**即可。

#### 梳理一下操作顺序：

1. 对所有组别的分数进行**排序**，并且分为数量相等的四组。
1. 使用随机数，生成每 $4$ 只队伍为一组，共 $\frac{n}{4}$ 组。
1. 按照组别**排序**，**编号**并输出。

**注意：一定要加** $\texttt{freopen}$**！一定要加！**
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct p
{
	string a;
	int b;
}all[70] , m1[20] , m2[20] , m3[20] , m4[20] , ans[5];
short n;
int x , a , b , c , tmp , q;
char ansc = 'A';
bool cmp(p l , p r)
{
	return l.b > r.b;
}
int randint()
{
	x = x * a + b;
	x %= c;
	return x;
}
void print()
{
	cout << "Group " << ansc << ":\n";
	ansc++;
	sort(ans + 1 , ans + 5 , cmp);
	for(int i = 1 ; i <= 4 ; i++)
	{
		cout << ans[i].a << endl;
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	freopen("input.txt" , "r" , stdin);
	freopen("output.txt" , "w" , stdout);
	cin >> n >> x >> a >> b >> c;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> all[i].a >> all[i].b;
	}
	sort(all + 1 , all + n + 1 , cmp);
	for(int i = 1 ; i <= n / 4 ; i++)
	{
		m1[i] = all[i];
	}
	for(int i = n / 4 + 1 ; i <= n / 2 ; i++)
	{
		m2[i - n / 4] = all[i];
	}
	for(int i = n / 2 + 1 ; i <= n / 4 * 3 ; i++)
	{
		m3[i - n / 2] = all[i];
	}
	for(int i = n / 4 * 3 + 1 ; i <= n ; i++)
	{
		m4[i - n / 4 * 3] = all[i];
	}
	n /= 4;
	tmp = n;
	for(int i = 1 ; i <= tmp ; i++)
	{
		q = randint() % n + 1;
		ans[1] = m1[q];
		for(int j = q ; j < n ; j++)
		{
			m1[j] = m1[j + 1];
		}
		q = randint() % n + 1;
		ans[2] = m2[q];
		for(int j = q ; j < n ; j++)
		{
			m2[j] = m2[j + 1];
		}
		q = randint() % n + 1;
		ans[3] = m3[q];
		for(int j = q ; j < n ; j++)
		{
			m3[j] = m3[j + 1];
		}
		q = randint() % n + 1;
		ans[4] = m4[q];
		for(int j = q ; j < n ; j++)
		{
			m4[j] = m4[j + 1];
		}
		n--;
		print();
	}
	return 0;
}
```

---

## 作者：Empty_Dream (赞：1)

## 题意

给你 $n$ 个球队，和四个作为随机数生成器的变量，再给出每个球队的名称和积分，让你通过某种随机数来进行分组。

分组方法：将 $n$ 个球队分到 $n/4$ 个盒子中，求出随机数 $x=(x \times a + b)\bmod c$，再抽取盒子中剩余球队编号为 $k \bmod s$ 的球队装进大组中，其中 $k$ 为随机数，$s$ 为盒子中剩余球队的数量。

抽象的题意理解完成之后，很容易看出来这是一道大模拟，稍微调一下代码就可以了。

## 分析

可以先将球队的积分从大到小排序，然后按照题意放进盒子中，然后将盒子中的元素通过随机数取出对应的元素放进大组中。

其中将积分从大到小的操作可以使用 ```vector``` 进行优化，通过 ```sort``` 和 ```reverse``` 可以实现，在进行从盒子中弹出的时候也可以用 ```erase``` 操作解决，优化了数组挪动的时间复杂度。

还有，这个题面好像没有说，原站上说了，要用文件读写。

## 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, x, a, b, c;
pair<int, string> v[105];
vector<pair<int, string>> w[5];
signed main(){
	freopen("input.txt", "r", stdin);//文件读写
	freopen("output.txt", "w", stdout);
	cin >> n >> x >> a >> b >> c;
	for (int i = 0; i < n; i++) cin >> v[i].second >> v[i].first;
	int m = n / 4;
	sort(v, v + n);
	reverse(v, v + n);//通过reverse实现从小到大变成从大到小
	for (int i = 0; i < n; i++) w[i / m].push_back(v[i]);//装进盒子里
	for (int i = 0; i < m; i++){
		printf("Group %c:\n", i + 'A');
		for (int j = 0; j < 4; j++){
			x = (x * a + b) % c;
			int pos = x % (m - i);//随机数
			printf("%s\n", w[j][pos].second.c_str());
			w[j].erase(w[j].begin() + pos);//从盒子里拿出来，放进大组中
		}
	}
	return 0;
}
```

---

## 作者：_xiaxii (赞：1)

# [题意传送门](https://www.luogu.com.cn/problem/CF234E)

~~本人的第一篇CF题解~~

## 题意理解

这是一道纯模拟题，按照题目所说的一步一步做就可以了。

题目要求将输入的每个队伍分成 $\frac{n}{4}$ 个队伍，且保证了 $n$ 为 $4$ 的倍数。每个队伍都有名字和分数两个熟悉，所以我们需要用结构题进行存储。首先需要先对每个队伍按照分数进行排序，最方便的就是直接调用 `sort()` 函数进行结构体排序。

用一个外循环遍历每个分组，再套一个内循环遍历每一个队伍。使用题目中所说的 $x=(x\times a + b) \bmod c$ 产生随机数，然后运用 `book` 数组标记此队伍是否已经被分组，再用一个 `while` 找到没有被分组的人数，当目前的人数等于所产生的随机数，则循环次数就是当前需要的队伍编号。将对应的输出就是答案了。

时间复杂度不高，不需要什么优化。

### 一些重要的东西
这类题需要文件输入输出，记得把 `freopen` 加上。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,x,q1,q2,q3;
int book[101];//使用book数组记录是否已加入

struct _grope{//定义_grope结构体记录每个队伍的信息
    string name;
    int grade;
}a[100];

bool cmp(_grope e,_grope r)
{
    return e.grade>r.grade;//按照得分从高到低排
}

int main()
{
    freopen("input.txt","r",stdin);//文件输入
    freopen("output.txt","w",stdout);//文件输出
    cin>>n>>x>>q1>>q2>>q3;//数据读入
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].name>>a[i].grade;
    }
    sort(a+1,a+n+1,cmp);//对每个队伍进行排序
    
    for(int i=1;i<=n/4;i++)
    {
        cout<<"Group "<<char('A'+i-1)<<":"<<endl;//这里一定要记得强制转化成char
        for(int j=1;j<=4;j++)
        {
            x=(x*q1+q2)%q3;//更新随机数
            int k=0,cnt=(j-1)*n/4+1;
            int m=x%(n/4-i+1);
            while(1)
            {
                if(!book[cnt]){
                    k++;
                    if(k==m+1)
                        break;//当当前剩下的队伍个数为随机数的值时break
                }
                cnt++;
            }
            book[cnt]=1;//标记此队伍已使用
            cout<<a[cnt].name<<endl;//输出此队伍
        }
    }
    return 0;//完美结束
}
```
实测[满分](https://www.luogu.com.cn/record/89341560)。

本[蒟蒻](https://www.luogu.com.cn/user/728002)的第三篇题解。

---

## 作者：开始新的记忆 (赞：1)

题目大意：给你n个人，给出每个人的名字及积分，要求按照题目所给的生成随机数的方法（y=(x*a+b)%c，x=y;）把这些人分组。

思路：其实这道题并没有用什么算法，纯模拟即可。只需在写代码的时候注意一下最后输出的每组中也是要从高到低排的。

code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std; 
struct node
{
    char name[25];
    int rating;
}team[70];
int n,m,x,y,a,b,c;
bool used[70];
bool cmp(node a,node b)
{
    return a.rating>b.rating;
}
int main()
{  
    freopen("input.txt","r",stdin);    
    freopen("output.txt","w",stdout); 
    int i,g,k,j,h,num;
    scanf("%d%d%d%d%d",&n,&x,&a,&b,&c);
    for (i=0;i<n;i++) 
        scanf("%s%d",team[i].name,&team[i].rating);
    sort(team,team+n,cmp);
    m=n/4;
    memset(used,false,sizeof(used));
    for (g=0;g<m;g++)
    {
           printf("Group %c:\n",'A'+g);
           for (k=0;k<4;k++)
           { 
                   y=(x*a+b)%c;
                   x=y;                  
                   h=x%(m-g); 
                   num=-1;
                   for (j=k*m;;j++)
                     if (!used[j])
                     {
                            num++;
                            if (num==h) break;
                     }
                   used[j]=true;
                   puts(team[j].name);                  
           }
    }
    return 0;
}
```


---

## 作者：xiaomimxl (赞：1)

## 题意：

如翻译所示，有 $n$ 个人。每个人有他们的名字和积分，给出一个随机数算法 $x=(x \times a+b) \bmod c$ 要把他们分成 $\dfrac{n}{4}$ 个组。 

## 分析：

题目理解起来有点麻烦，但读懂了就好了，就是要先分四个等级，然后每个队用随机数在每个组中选一个就可以了。

注意输出也要排序。

还有，此题需要文件输入输出。

## Code:

```cpp
#include<bits/stdc++.h>
const int N = 1000+5;
using namespace std;
 
struct Node{
    char name[N];
    int num;
    bool operator <(const Node &rhs)const{//重载运算符，不需要写cmp 
        return num>rhs.num;
    }
}team[N];
bool vis[N];//记得每个人只能选一次 
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    int x,a,b,c;
    scanf("%d",&n);
    scanf("%d%d%d%d",&x,&a,&b,&c);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%s",team[i].name);
        scanf("%d",&team[i].num);
    }
    sort(team,team+n);
 
    int group=n/4;
    for(int i=1;i<=group;i++){
        printf("Group %c:\n",'A'+i-1);
        for (int k=1;k<=4;k++) {
            x=(x*a+b)%c;
            int val=x%(group-i+1);
            int num=0;
            int cnt=(k-1)*group;
            while(true){//处理重复，找到人 
                if(!vis[cnt]){
                    num++;
                    if(num==val+1)
                        break;
                }
                cnt++;
            }
            vis[cnt]=true;
            printf("%s\n",team[cnt].name);
        }
    }
    return 0;
}
```


---

## 作者：Kyl_in_2024 (赞：0)

**前言**

洛谷题面根本没提到有 freopen，~~幸亏我看的是原题。~~

这个翻译也不知所云……只能说一下题目大意了。有点长，懂的大佬跳过。

**题目大意和部分思路**

有 $n$ 个球队（$n$ 能被 $4$ 整除）现在要把这些球队分组。

首先把球队按照给出的分数排序，然后从前往后平均分成四队，随后进行 $\frac{n}{4}$ 次操作。

对于每次操作：遍历每个队，假设当前队里有 $x$ 个人，而且是按照得分高低排序的。使用随机数生成器生成一个数 $k$，然后把第 $(k \bmod x) + 1$ 个人（+1 是因为从 1 开始）放到一个新的队里（退出原来的分组），然后遍历完四个队就把这个新队输出。

接着就是按题意模拟。

对于随机数生成器，不是真的随机数生成器，而是计算 $y = ( x \times a + b ) \bmod c$，然后返回 $y$ 作为生成的随机数，最后赋值 $x = y$。

看起来挺难，其实写的时候没那么折磨，注意 freopen 就行了。但是我写的挺长，没怎么压行。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Player{
	string name;
	int score;
}p[70]; 
bool cmp(Player a,Player b){
	return a.score>b.score;
}//以上都是结构体的定义
bool vis[70];
int n,x,a,b,c;
void random(){
	x=(x*a+b)%c;
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>x>>a>>b>>c;
	for(int i=1;i<=n;i++){
		cin>>p[i].name>>p[i].score;
	}
	sort(p+1,p+n+1,cmp);
	for(int i=n/4;i>=1;i--){
		char c='A'+(n/4-i);
		cout<<"Group ";
		cout<<c<<":\n";
		for(int q=0;q<4;q++){
			random();
			int k=q*(n/4);
			for(int j=0;j<=x%i;j++){
				k++;
				while(vis[k]) k++;
			}
			cout<<p[k].name<<"\n";
			vis[k]=1;
		}
	}
	return 0;
}
```

感谢题解审核员高强度（一天 900 篇）的审核以及耐心地指出错误。

---

