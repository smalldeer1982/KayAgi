# Warehouse

## 题目描述

**注意：需要文件输入输出，输入文件为 input.txt，输出文件为 output.txt**

仓库里有一个高为 $n$，宽为 $m$ 的架子，即 $n \times m$ 的一个架子。DravDe 会进行 $k$ 次操作，每次操作他会往这个架子上的一个位置放进或拿出一个箱子。

如果 DravDe 要放一个箱子，他会先看这个位置上是不是已经有箱子了，如果有则放入右边的位置；如果右边也有箱子，则以此类推。如果到了此行的第 $m$ 列还有箱子，他会放入下一行的第一列，并重复上述操作。如果到最后都找不到，他会把箱子丢掉，不放到架子上。

如果 DravDe 要拿出一个箱子，你需要输出这个箱子所在的坐标 $(i,j)$，表示这个箱子被放在了第 $i$ 行第 $j$ 列，并拿走它。**这个箱子可能不存在**。

## 样例 #1

### 输入

```
2 2 9
+1 1 1 cola
+1 1 1 fanta
+1 1 1 sevenup
+1 1 1 whitekey
-1 cola
-1 fanta
-1 sevenup
-1 whitekey
-1 cola
```

### 输出

```
1 1
1 2
2 1
2 2
-1 -1
```

## 样例 #2

### 输入

```
2 2 8
+1 1 1 cola
-1 cola
+1 1 1 fanta
-1 fanta
+1 1 1 sevenup
-1 sevenup
+1 1 1 whitekey
-1 whitekey
```

### 输出

```
1 1
1 1
1 1
1 1
```

# 题解

## 作者：alex_liu (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF35B)

这道题其实挺有意思的，考你细心的程度
# 思路：
直接模拟两种操作就好了，用结构体存每一个箱子会比较简单一些。

每一条语句的详细意思可以看注释。
# 代码块部分：
**结构体：**
```cpp
struct box{
	int x,y;//箱子的坐标 
	string id;//箱子的名字 
}a[10005];
```
**文件读写：**
```cpp
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);//文件读写 
```
**摆放箱子的操作：**
```cpp
if(opt==1){//操作 1 
	int xx,yy;
	cin>>xx>>yy>>name;//输入坐标及名称 
	if(s[xx][yy]==false){//格子为空，可直接放入 
		cnt++;//成功放入柜子 
		a[cnt].x=xx,a[cnt].y=yy,a[cnt].id=name;//赋值 
		s[xx][yy]=true;//格子已满 
	}else{//格子不为空，需要移动 
		if(yy==m){
			yy=1;
			xx++;
		}
		else yy++;//初始化 
		while(s[xx][yy]==true&&xx<=n){//找到合适的位置且没有越界 
			yy++;
			if(yy-1==m){
				yy=1;
				xx++;
			}
		}
		if(xx<=n){//找到了可放的格子 
			cnt++;//成功放入柜子 
			a[cnt].x=xx,a[cnt].y=yy,a[cnt].id=name;//赋值 
			s[xx][yy]=true;//格子已满 
		}
	}
}
```
**取出箱子的操作：**
```cpp
else{//操作2 
	bool tf=true;//布尔值代表是否找到箱子（找到为 false ，否则为 true ） 
	cin>>name;//输入 
	for(int j=1;j<=cnt;j++){//循环查找 
		if(a[j].id==name){//找到箱子 
			cout<<a[j].x<<" "<<a[j].y<<endl;//输出 
			tf=false;//布尔值改变 
			s[a[j].x][a[j].y]=false;//此格子为空 
			a[j].x=-1,a[j].y=-1; 
			a[j].id="";//此箱子的各个数据设置为不可能再次查找到的值
			break;//退出循环 
		}
	}
	if(tf==true)puts("-1 -1");//未找到箱子 
}
```
# 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct box{
	int x,y;//箱子的坐标 
	string id;//箱子的名字 
}a[10005];
bool s[50][50];// s[i][j] 表示柜子的第 i 行 j 列的格子（ false 代表空， true 代表满，这里默认初始化每个格子都为空） 
int n,m,k,cnt=0;// cnt 为箱子已成功放入柜子的个数 
int main(){
	freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);//文件读写 
	cin>>n>>m>>k;//输入 
	for(int i=1;i<=k;i++){
		int opt;
		cin>>opt;//输入操作 
		string name;
		if(opt==1){//操作 1 
			int xx,yy;
			cin>>xx>>yy>>name;//输入坐标及名称 
			if(s[xx][yy]==false){//格子为空，可直接放入 
				cnt++;//成功放入柜子 
				a[cnt].x=xx,a[cnt].y=yy,a[cnt].id=name;//赋值 
				s[xx][yy]=true;//格子已满 
			}else{//格子不为空，需要移动 
				if(yy==m){
					yy=1;
					xx++;
				}
				else yy++;//初始化 
				while(s[xx][yy]==true&&xx<=n){//找到合适的位置且没有越界 
					yy++;
					if(yy-1==m){
						yy=1;
						xx++;
					}
				}
				if(xx<=n){//找到了可放的格子 
					cnt++;//成功放入柜子 
					a[cnt].x=xx,a[cnt].y=yy,a[cnt].id=name;//赋值 
					s[xx][yy]=true;//格子已满 
				}
			}
		}else{//操作2 
			bool tf=true;//布尔值代表是否找到箱子（找到为 false ，否则为 true ） 
			cin>>name;//输入 
			for(int j=1;j<=cnt;j++){//循环查找 
				if(a[j].id==name){//找到箱子 
					cout<<a[j].x<<" "<<a[j].y<<endl;//输出 
					tf=false;//布尔值改变 
					s[a[j].x][a[j].y]=false;//此格子为空 
					a[j].x=-1,a[j].y=-1; 
					a[j].id="";//此箱子的各个数据设置为不可能再次查找到的值
					break;//退出循环 
				}
			}
			if(tf==true)puts("-1 -1");//未找到箱子 
		}
	}
    return 0;
}

```


---

## 作者：windowshappy (赞：2)

题意为有一个 $n \times m$ 的架子会进行 $ k $ 次操作，当为 `+1` 时放入，当为 `-1` 时取出如果不存在输出 `-1 -1` 。

这题可以用 2 个 `map` 一个存坐标，一个存是否存在,用一个结构体代表坐标：
```cpp
struct ppp {
    int x, y;
    bool operator<(const ppp &b) const {
        if (x < b.x)
            return true;
        else if (y < b.y && x == b.x)
            return true;
        else
            return false;
    }
    bool operator==(const ppp &b) const {
        if (y == b.y && x == b.x)
            return true;
        else
            return false;
    }
};
map<string, ppp> mp;
map<ppp, bool> mp1;
```
当为 `+1` 时，用 **while** 循环找到空位置，如果没有则放弃：
```cpp
if (t == "+1") {
    cin >> x >> y >> name;
    ppp t = (ppp){x, y};
    bool f = true;
    while (mp1[t]) {
        t.y++;//向右遍历
        if (t.y > m) {//如果超了
            t.x++;//行加1
            t.y = 1;//列等于1
            if (t.x > n) {//如果超了将标识设为false，退出循环
                f = false;
                break;
            }
        }
    }
    if (f) {//如果有空位
        mp[name] = t;
        mp1[t] = true;
    }
}
```
当为 `-1` 时，如果找得到，就输出坐标并在 **map** 里删除，如果找不到，就输出 `-1 -1`:
```cpp
else {
    cin >> name;
    if (mp.find(name) != mp.end()) {//找得到
        ppp t = mp[name];
        cout << t.x << " " << t.y << endl;
        mp.erase(name);//删除
        mp1[t] = false;//设为空
    } else {//找不到
        cout << "-1 -1\n";
    }
}
```


注意：需要文件输入输出，输入文件为 input.txt，输出文件为 output.txt ，否则会 $\text{\color{#FF0000} WA}$ 。

```cpp
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
```

**AC CODE**
```cpp
#include<bits/stdc++.h>

using namespace std;
struct ppp {
    int x, y;
    bool operator<(const ppp &b) const {
        if (x < b.x)
            return true;
        else if (y < b.y && x == b.x)
            return true;
        else
            return false;
    }
    bool operator==(const ppp &b) const {
        if (y == b.y && x == b.x)
            return true;
        else
            return false;
    }
};
map<string, ppp> mp;
map<ppp, bool> mp1;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m, k;
    cin >> n >> m >> k;
    string t, name;
    int x, y;
    while (k--) {
        cin >> t;
        if (t == "+1") {
            cin >> x >> y >> name;
            ppp t = (ppp){x, y};
            bool f = true;
            while (mp1[t]) {
                t.y++;
                if (t.y > m) {
                    t.x++;
                    t.y = 1;
                    if (t.x > n) {
                        f = false;
                        break;
                    }
                }
            }
            if (f) {
                mp[name] = t;
                mp1[t] = true;
            }
        } else {
            cin >> name;
            if (mp.find(name) != mp.end()) {
                ppp t = mp[name];
                cout << t.x << " " << t.y << endl;
                mp.erase(name);
                mp1[t] = false;
            } else {
                cout << "-1 -1\n";
            }
        }
    }
    return 0;
}
```


---

## 作者：_Spectator_ (赞：1)


[可能更好的食用体验](/blog/523641/CF35B) $|$ 
[题目传送门](/problem/CF35B) $|$ 
[我的其他题解](/blog/523641/#type=题解)

------------

${\large\color{#00CD00}\text{主要思路}}$

这道题其实是一道很简单的模拟题。可以分两部分来考虑。

**1.放箱子**

令我疑惑的是题解区为什么没有递归的做法？递归虽然时间复杂度不算优秀，但胜在其码量少且易理解。根据题目的描述，我们可以写出以下的递归函数：
```cpp
//id是箱子的名称，h和l用于存储箱子的位置，这个后面会写
void pull(int x,int y)   
{　
	if(x>n)return;//当行数超出范围，说明没有空间放箱子了，直接退出
	if(y>m)pull(x+1,1);//当列数超出范围，放到下一行第一个
	else if(f[x][y])pull(x,y+1);//当该格子有箱子，放到该行下一个
	else{f[x][y]=1,h[id]=x,l[id]=y;return;}//否则，将箱子放到该格子上
}　
```
这样就解决了放箱子的问题。

**2.取箱子**

由于箱子的 $id$ 是一个字符串，所以可以用`map`（映射）来存储箱子的坐标。取箱子时，只需要判断一下该箱子是否存在，输出该箱子的坐标并取出即可。
```cpp
map<string,int>h,l;//用于存储箱子的坐标
if(h[id]!=0)//判断该箱子是否存在
{　
	cout<<h[id]<<' '<<l[id]<<endl;　
	f[h[id]][l[id]]=0,h[id]=0,l[id]=0;//取出该箱子
}　
else cout<<"-1 -1\n";　
```

------------

${\large\color{#00CD00}\text{完整代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,o,x,y;
string id;
bool f[35][35];
map<string,int>h,l;
void pull(int x,int y)
{　
	if(x>n)return;
	if(y>m)pull(x+1,1);
	else if(f[x][y])pull(x,y+1);
	else{f[x][y]=1,h[id]=x,l[id]=y;return;}
}　
int main()
{　
	//一定要加文件读写！！！
	freopen("input.txt","r",stdin);　
	freopen("output.txt","w",stdout);　
	cin>>n>>m>>k;　 
	for(int i=1;i<=k;i++)
	{　
		cin>>o;　
		if(o==1)cin>>x>>y>>id,pull(x,y);　
		if(o==-1)　
		{　
			cin>>id;　
			if(h[id]!=0)　
			{　
				cout<<h[id]<<' '<<l[id]<<endl;
				f[h[id]][l[id]]=0,h[id]=0,l[id]=0;
			}　
			else cout<<"-1 -1\n";
		}　
	}　
	return 0;
}　
```

**[${\color{Black}\textbf{xt\_\_}}$](/user/523641) 温馨提示：**


${\large\color{White}\text\colorbox{#AD8800}{题解千万条，理解第一条。直接粘题解，棕名两行泪。}} $

---

## 作者：tanghg (赞：1)

这道题的思路是模拟。

### 题目大意：

一个架子放箱子，有两种操作：

- ”+1“:从架子坐标 $(x,y)$ 开始放箱子，位置有东西了就去右边的一个。一排满了去下一排，如果都满了就把箱子扔了。
- ”-1“:给一个箱子的名字，让你去输出箱子在架子上的坐标，没有箱子输出 $-1,-1$。

### 思路：

这题要文件输入输出
```cpp
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

现在我们首先可以想到吧名字存在一个 string 的二维数组中，然后对两种思路进行模拟。

#### +1 部分：

因为在 $x$ 行的架子是从一个不完整的地方去判断是否要放的，所以我们可以单独先把那一排给挑出来先判断，这样如果放下了就没问题，如果箱子还在就可以直接从下一排查看到头。我把数组先初始化成 0，用来判断是否为空格子。
#### -1 部分：

这个没有什么好说的吧，从头查一遍架子有一样的输出就好了。然后插个旗去判断 $-1,-1$ 的情况即可。如果有就把格子清空或是说变成 0。

代码 60 多行就放剪贴板了，我自认为还算好理解。

[代码](https://www.luogu.com.cn/paste/cs145tih)

还请不要抄袭，谢谢。


---

## 作者：yingkeqian9217 (赞：1)

这题不是特别难，就是要注意 `freopen` 我就是被坑了。

注意这里是从 `(x,y)` 开始，不是求矩形，所以第一行要特判。

话不多说上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
string s[1501][1501];
void add(int x,int y,string str){
	for(int i=y;i<=m;i++) if(s[x][i]==""){s[x][i]=str;return;}//先遍历第一行，因为这有这一行从y开始
	for(int i=x+1;i<=n;i++)//下面几行，常规操作
	 for(int j=1;j<=m;j++)
	  if(s[i][j]==""){
	  	s[i][j]=str;
	  	return;//如果是空的，就可以放，直接return
	  }
}
int main(){
	int c,x,y;
	string str;
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);//不要忘
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++){
		cin>>c;
		if(c==1){
			cin>>x>>y>>str;
			add(x,y,str);//懒得直接写qwq
		}
		else{
			bool b=0;
			cin>>str;
			for(int j=1;j<=n;j++)
			 for(int k=1;k<=m;k++)
			  if(s[j][k]==str){
			  	cout<<j<<' '<<k<<endl;
			  	s[j][k]="";
			  	b=1;
			  	break;
			  }
			if(b!=1) cout<<-1<<' '<<-1<<endl;//b判断是否可以搜到
		}
	}
	return 0;
}
```


---

## 作者：白いバラの夜 (赞：1)

#### 这道题其实说难也不难，就是翻译的问题，当是1 的时候就往架子的盒子里面放东西，盒子里有东西就往下找空的位置，再接着放，当是-1从盒子里往外拿东西，并输出坐标
```cpp
#include<stdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,tp[100][100],x,y,k;
char aa[20];
struct mm{
    char ss[50][50];
}vv[500];
void init(){
    for(int i=0;i<= n;i++){
        for(int j=0;j<=m;j++){
            tp[i][j]=0;
        }
    }
}
void add(){
    int flag=0;
    if(!tp[x][y]){
        tp[x][y]=1;
        strcpy(vv[x].ss[y],aa);
    }else{
        int pp=y;
        for(int i=x;i<=n;i++){
            for(int j=pp;j<=m;j++){
                if(!tp[i][j]){
                    tp[i][j]=1;
                    strcpy(vv[i].ss[j],aa);
                    flag=2;
                    break;
                }
            }
            pp=1;
            if(flag){
            	break;
			}
        }
    }
}
void mov(){
    int flag=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!strcmp(vv[i].ss[j],aa)&&tp[i][j]){
                printf("%d %d\n",i,j);
                flag=2;
                tp[i][j]=0;
                break;
            }
        }
        if(flag){
        	break;
		}
    }
    if(!flag){
    	puts("-1 -1");
	}
}
int main(){
    int a;
    while(~scanf("%d%d%d", &n,&m,&k)){
        init();
        memset(vv,' ',sizeof(vv));
        for(int i=0;i<k;i++){
            scanf("%d",&a);
            if(a>0){
                scanf("%d%d%s",&x,&y,aa);
                add();
            }else{
                scanf("%s",aa);
                mov();
            }
        }
    }
}
```


---

## 作者：lidundun (赞：0)

# Warehouse
纯模拟，注意下细节就好。

$xy$ 表示矩阵行列数，$n$ 表示执行动作次数，$mp$ 表示箱子的名字。顺便建议大家把答案存起来结尾输出，比赛有些题目格式抓得很紧。

由于数据较小，可以每次执行都把矩阵遍历一遍，查找空位放箱子或者找到相应的箱子取出。


# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,n,a,b,cnt,ans[2010][5];
string t,s,mp[35][35];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d%d",&x,&y,&n);
	for(int i=1;i<=n;i++)
	{
		cin>>t;//比scanf好处理，时间允许的情况推荐
		if(t=="+1")
		{
			scanf("%d%d",&a,&b);
			cin>>s;
			while(mp[a][b]!=""&&a<=x)
			{
				b++;
				if(b>y)
				{
					b=1;
					a++;
				}
			}
			if(a<=x)  mp[a][b]=s;
		}
		else
		{
			cin>>s;
			ans[++cnt][1]=-1;
			ans[cnt][2]=-1;
			for(int j=1;j<=x;j++)
			{
				for(int k=1;k<=y;k++)
				{
					if(mp[j][k]==s)
					{
						ans[cnt][1]=j;//储存答案
						ans[cnt][2]=k;
						mp[j][k]="";
					}
				}
			}
		}
	}
	for(int i=1;i<cnt;i++)  printf("%d %d\n",ans[i][1],ans[i][2]);
	printf("%d %d",ans[cnt][1],ans[cnt][2]);//最后一行不换行
	return 0;
}
```
~~话说为什么AC代码又交了两遍都WA了？？？~~

---

## 作者：_wjr_ (赞：0)

题目描述已经很清楚了，在此就不多做赘述了。

## 思路

这道题是一道模拟题，我们只需考虑把箱子放到架子上和把箱子取下来这两种操作就行了。

### 把箱子放到架子上

原题给出了一个坐标 $(x,y)$ ，让我们把箱子放到这个位置之后第一个空位上。如果没有，就把这个箱子扔掉。

我们可以用一个二维数组 $a$ 表示这个书架，这上面的每个位置都可以在二维数组上表示出来。如果在 $a_{x,y}$ 这个位置上为空，那么就把箱子放在这里。否则，我们依次看看 $a_{x, y + 1} , a_{x,y+2} , \cdots$，直到有一个位置为空，就把它放进去。这个步骤用一个 while 循环即可。

### 把箱子取出来

我们发现，这题给出的 $n , m$ 的范围都特别小，我们由此可以暴力枚举一遍，看看到底在哪个位置有这个箱子。

于是，我们就又过了一道题。

## 易错点

这道题其实没有什么太容易错的地方，但是需要注意：

1. 把箱子放到架子上时，需要注意到考虑下一行和整个书架都没有空位的情况。
2. 需要用到文件输入输出
3. 很多题中最重要的一点：不开 long long 见祖宗。

**接下来，献上 AC 代码！**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

string a[110][110];

signed main()
{
    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++)
    {
        string f;
        cin >> f;
        if (f == "+1") //要注意这里是 +1 而不是 1
        {
            int x, y;
            string id;
            bool flag = true;
            cin >> x >> y >> id;
            while (a[x][y] != "")
            {
                y++;
                if (y == m + 1) //这一行没有位置
                {
                    y = 1;
                    x++;
                }
                if (x > n) //整个书架都没有位置
                {
                    flag = false;
                    break;
                }
            }
            if (flag) a[x][y] = id;
        }
        else
        {
            string id;
            bool flag = false;
            cin >> id;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                {
                    if (a[i][j] == id) //循环找答案
                    {
                        cout << i << " " << j << endl;
                        flag = true;
                        a[i][j] = "";
                        break;
                    }
                }
            
            if (!flag) cout << "-1 -1" << endl;
        }
    }
    return 0;
}
```


---

## 作者：dks0311 (赞：0)

### 题意
有一个 $n \times m$ 的网格。两种操作：第一种将箱子放在指定位置，若该位置有箱子则一直往右移，移到第 $m + 1$ 列则移到下一行第一列，知道找到一个空位置将箱子放上去。第二种操作将指定箱子拿走并输出其位置，若没有则输出 $-1$。

### 思路
箱子的 $id$ 是字符串，可以开一个 map 记录每一个箱子的位置，一个储存是否存在，没有的为 $(0,0)$。每次放箱子就 while 暴力往后找空位置就行。第二个操作直接调用 map 存的位置。

### 代码
```
#include<bits/stdc++.h>
const int N = 2e3 + 5;
inline int read(){
	int s = 0, f = 0;
	char ch = getchar();
	while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
	while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0', ch = getchar();
	return f ? ~s + 1 : s;
}
int n, m, k;
bool vis[35][35];
struct node{int x, y;};
std::unordered_map<std::string, node> mp;
std::unordered_map<std::string, bool> b;
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout); //之前忘了打这玩意，查了半天错 
	n = read(), m = read(), k = read();
	while(k --){
		int opt = read();
		if(opt == 1){
			int x = read(), y = read();
			std::string s; std::cin >> s;
			while(vis[x][y]){ //找空位置 
				++ y;
				if(y == m + 1) ++ x, y = 1; //越界则调到下一行 
			}
			if(x == n + 1) continue;
			vis[x][y] = true;
			mp[s] = (node){x, y};
			b[s] = true;
		}
		else{
			std::string s; std::cin >> s;
			if(!b[s]){
				puts("-1 -1");
				continue;
			} //不存在 
			node tmp = mp[s];
			printf("%d %d\n", tmp.x, tmp.y); 
			vis[tmp.x][tmp.y] = false;
			mp[s] = {0, 0};
			b[s] = false;
		}
	}
	return 0;
}
```

---

## 作者：zhmzhuhanming (赞：0)

# [题目传送器](https://www.luogu.com.cn/problem/CF35B)

这道 普及- 的题目竟然把本人坑了好久，其中一个原因当然还是那前有古人，后有来者的:

freopen! freopen! ! freopen! ! !

这题呢，写代码时好像有些繁琐，但写出来就不过于模拟几下：放入箱子和取出箱子。

- 放入箱子时，从给出的 $x,y$，可以每次把从坐标加 $1$，如果到第 $m$ 列了，则换到下一行的第一列，继续列数加加。

- 取出箱子时，就更简单了，把所有位置遍历一遍就行了，要注意的是，取出箱子指的是把那个位置的箱子拿走，记得把存储在那个位置的 $name$ 给删除，不然下次查询又会返回这里的位置。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k;
string a[100][100];//本人作死开了个100*100的数组，也不知剩下的70寂不寂寞
signed main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);//最后一遍，freopen!!!
	cin>>n>>m>>k;
	for(int l=1;l<=k;l++){   //k次操作
		char c1,c2;
		cin>>c1>>c2;
		if(c1=='+'&&c2=='1'){	//如果是放入操作
			int x,y;
			string s;
			cin>>x>>y;		//箱子的位置
			cin>>s;			//箱子的名字
			int i=x,j=y;
			while(1){
				if(a[i][j]==""){		//找到空位置了
					a[i][j]=s;			//放入箱子
					break;				//直接退出
				}
				if(j==m&&i<n){			//如果不是最后一行但是最后一列
					i++,j=0;			//到下一行第一列
				}
				else if(j==m&&i==n)break;	//如果到最后一个位置了，就退出
				j++;					//下一个位置
			}
		}
		else if(c1=='-'&&c2=='1'){		//取出操作
			string s;
			cin>>s;
			bool o=0;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					if(a[i][j]==s){
						printf("%lld %lld\n",i,j);//找到就可以输出了
						o=1;			//标记找到了
						a[i][j]="";		//取出箱子
						break;			
					}
				}
			}
			if(!o)printf("-1 -1\n");	//如果没找到过，就输出-1 -1
		}
	}
	return 0;
}
```


---

## 作者：Tobiichi_Origami (赞：0)

这道题就是**模拟！模拟！还是模拟！**

**题目大意**

有一个有 $n$ 乘 $m$ 个格子的柜子，要你放箱子，有两种操作：

- 输入 $+1$，在坐标点放箱子。如果格子满了，则在它的右边一个格子放箱子，然后以此类推。一排都不行就换下一排，直到放下去。如果怎么也放不下去就扔了。
- 输入 $-1$，在架子上查找一个名字，有则拿出，没有则输出。

**思路**

- $+1$：先判断输入的坐标可不可以放进去，能放就存到结构体中，不能就依次枚举右边的坐标直到找到一个空的格子，放到结构体中。
- $-1$：遍历一遍结构体，如果找到了就输出坐标，再把格子设为空，把 $\texttt{flag}$ 设为 $\texttt{true}$。如果 $\texttt{flag}$ 为 $\texttt{false}$ 就输出 $-1$ $-1$。

**贴代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,j;
struct node{
	int x,y;//坐标
	string id;//名称
}a[1000010];
bool vis[51][51];//标记数组
void put(int dx,int dy,string num)//放格子
{
        j++;//更新
	a[j].x=dx;
	a[j].y=dy;
	a[j].id=num;//放入
	vis[dx][dy]=0;//标记为满
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	memset(vis,1,sizeof(vis));//初始化
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++)
	{
		string s;
		cin>>s;
        //放箱子
		if(s=="+1")
		{
			int dx,dy;
			string num;
			cin>>dx>>dy>>num;//输入
			if(!vis[dx][dy])//格子不为空
			{
				if(dy==m)
				{
					dy=1;
					dx++;
				}
				else dy++;
				while(!vis[dx][dy]&&dx<=n)//找空格子并且不越界
				{
					dy++;//寻找下一个
					if(dy-1==m)//判断换行
					{
						dy=1;
						dx++;
					}
				}
				if(dx<=n)//找到了空格子
				{
					put(dx,dy,num);
				}
			}
			else//格子为空
			{
				put(dx,dy,num);
			}	
		}
		else//拿出箱子
		{
			bool flag=0;
			string num;
			cin>>num;
			for(int l=1;l<=j;l++)
			{
				if(a[l].id==num)//当找到这个箱子
				{
					cout<<a[l].x<<" "<<a[l].y<<endl;
					flag=1;//标记为找到
					vis[a[l].x][a[l].y]=1;//标记为空
					a[l].x=a[l].y=-1;
					a[l].id="";//标记为空
					break;
				}
			}
			if(!flag) cout<<"-1 -1"<<endl;//没有这个名字的箱子
		}
	}
	return 0;
}
 

```


---

