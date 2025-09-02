# [CERC2017] Assignment Algorithm

## 题目描述

一家航空公司正在设计一种复杂的算法，将为提前购票的乘客分配更理想的座位。他们的飞机有 $r$ 排座位，其中 $r$ 是一个偶数。飞机上有 $3$ 行出口行，这些排没有座位，只提供通往紧急出口的通道。一个出口排在飞机的最前面（在第一排座椅之前），一个在最后面（在最后一排座椅之后），另一个在中间的位置。这些行用整数 $1$ 到 $r+3$ 进行编号，行号从飞机前部到后部递增。

编号为 $1$、$r/2+2$ 和 $r+3$ 的行是出口行，而所有其他行都是座位行。
座位配置为 “$3–3–3$” 每排座位包含三个组三个座位，每组座位之间有乘客通道。同一排座位用从左到右的连续字母表示，对应于“``ABC.DEF.GHI``”模式。
当乘客购买机票时，会根据以下规则为其分配座位：

1.如果在出口排的正后方有一排空座位，则在接下来的步骤中忽略所有其他排（但在最后一步中平衡飞机时不忽略）。

2.首先，我们选择空座位数最多的一排座位。如果有多个这样的行，则选择最靠近出口行的行（行 $a$ 和 $b$ 之间的距离仅为 $|a− b|$）。如果仍有多个这样的行，则选择编号最低的行。

3.现在，我们考虑所选行中的空座位，并选择一个优先级最高的座位。座位优先级从高到低排序按照如下规则：\
-（a）中间组的过道座位（即`D`或`F`）。\
-（b）第一组和第三组的过道座位（即``C``或``G``）。\
-（c）靠窗座位（即``A``或``I``）。\
-（d）中间组中的中间座位（即`E`）。\
-（e）第一组和第三组的中间座位（即``B``或``H``）。\
如果有两个空座位具有相同的最高优先级，我们会考虑整个飞机的平衡。飞机左侧包含字母``A``、``B``、`C`或`D`的所有座位，而右侧包含字母`F` 、`G`、`H`或 `I` 的所有座位。我们在空座位较多的一侧选择一个空座位。如果两边有相同数量的空座位，则优先选择飞机左侧的座位。\
飞机的一些座位已经预定好了（即输入中的 `#`）。现在请你确定分配给第 $i$ 个购票的乘客的座位。

## 样例 #1

### 输入

```
2 17
...........
---.#--.---
...........
---.---.---
...........
```

### 输出

```
...........
hnd.#lb.fpj
...........
kqg.cma.eoi
...........
```

## 样例 #2

### 输入

```
6 26
...........
---.---.###
#-#.---.---
---.###.---
...........
---.###.---
#--.#-#.--#
#--.--#.#-#
...........
```

### 输出

```
...........
gke.aic.###
#-#.mzo.r-v
x-p.###.n-t
...........
fjb.###.dlh
#-s.#-#.w-#
#-u.qy#.#-#
...........
```

# 题解

## 作者：warmingcium (赞：2)


差一点点就抢到最优解啦~

### 题意简述

飞机座位共有 $n$ 排可以坐，第 $1$ 排前面、第 $\frac{n}{2}$ 排后面以及最后一排后面是安全通道，一排有 $9$ 个座位依次编号为$ABC.DEF.GHI$。

在安全通道后面第一排的位置应先进行安排，当安全通道后面第一排位置都安排满了，每一排空位越多越先安排；若多排空余位置数目相同，越靠近安全通道越先安排；如果距离安全通道距离相同，则应从前往后安排。你在安排一排座位的时候安排顺序为：当 $D F$ 空的时候先安排 $D F$ ，然后 $C G$ 空的时候安排 $C G$ ，$A I$空的时候安排 $A I$， $E$ 空的时候安排 $E$ ，$B H$ 空的时候安排 $B H$ 。

当两个位置的优先级相同并且可以都可以安排的时候，如果左方人数小于等于右方人数的时候先安排左方的位置，否则先安排右方的位置。

### 模拟策略

1. 安全通道后面第一排先安排。

2. 每一排空余位置越多越先安排。

3. 距离安排通道越近越先安排。

4. 字典序小的先安排。

5. 每一排按照给定的顺序安排。

6. 飞机两边哪边人数小哪边安排，相等安排在左方。

### 代码实现

 - 我用变量 $cntR$ 记录每一排有多少个空余的位置。
 - 用变量 $cntl$ 记录飞机左边有多少人。
 - 用变量 $cntr$ 记录飞机右边有多少人。
 - 用变量 $dir$ 记录每一排的安排顺序。
 - 用变量 $dis$ 记录每一排距离安全通道的距离。
 
依照上述模拟策略，我们只需要按照 $26$ 个字母顺序把对应的人放进去即可，只要读题没有问题并且有**亿点点**耐心调试都没有问题啦~

```

#include <bits/stdc++.h>
using namespace std;
const int maxn = 55;
const int maxm = 19;
char s[maxn][maxm];
int n,m,cntR[maxn],cntl,cntr,dir[10]={0, 5, 3, 1, 6, 2},dis[maxn];
int findR(){
    int Max=-1,R=0;
    if(cntR[2] == 0 && cntR[3+n/2] == 0){
        for(int i = 1; i <= n+3; i++){
            if(cntR[i] > Max){
                Max = cntR[i];
                R = i;
            } else if(cntR[i] == Max) {
                if(dis[i]<dis[R]) {
                    R=i;
                }
            }
        }
    }else{
        if(cntR[2] >= cntR[3+n/2]) return 2;
        else return 3+n/2;
    }
    return R;
}
int findC(int R) {
    for(int i=1;i<=5;i++) {
        int now=dir[i];
        int pos1=now;
        int pos2=12-now;
        if(s[R][pos1]=='-'&&s[R][pos2]=='-') {
            if(cntl<=cntr) return pos1;
			else return pos2;
        } else if(s[R][pos1] == '-') {
            return pos1;
        } else if(s[R][pos2] == '-') {
            return pos2;
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n+3;i++) {
        scanf("%s",s[i]+1);
        int cnt=0;
        for(int j=1;j<=11;j++){
            if(s[i][j]=='-') cnt++;
            if(s[i][j]=='#') {
                if(j<=5) cntl++;
                if(j>=7) cntr++;
            }
        }
        if(i<3+n/2) dis[i] = min(i-1, (2+n/2)-i);
		else dis[i]=min(i-(2+n/2), (n+3)-i);
        cntR[i]=cnt;
    }
    for(int i=0;i<m;i++){
        int R=findR();
        int C=findC(R);
        if(C<6) cntl++;
        else if(C>6) cntr++;
        s[R][C]=i+'a';
        cntR[R]--;
    }
    for(int i=1;i<=n+3;i++) {
        printf("%s\n",s[i]+1);
    }
    return 0;
}

```

---

## 作者：xxxalq (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P4736)

## 思路分析：

这就是一道大模拟。

我们只需要按照题目中的要求一步一步来即可：

这里我们先确定行，再确定列。

首先判断门后一排是否有空座位，如果有就确定为这一行。如果没有按照空位最多、靠门最近、编号最小来确定行。

确定列按照题目中优先级判断即可。

两个优化：开一个数组统计每行空位数量；用两个变量分别存储飞机左右两边做了多少人一次来保证平衡。

## 代码：

```cpp
#include<iostream>
using namespace std;
int r,n,now=96,Left,Right,Row[55],maxidx;//Row存储每行空位，Left和Right存储左右两边人数 
char a[60][15];
const int inf=0x3f3f;
int check_door(){//判断门后一排是否有空座，返回排数，否则返回0 
	for(int i=1;i<=11;i++){
		if(a[2][i]=='-'){
			return 2;
		}
	}
	for(int i=1;i<=11;i++){
		if(a[r/2+3][i]=='-'){
			return r/2+3;
		}
	}
	return 0;
}
int Min(int x,int y,int z){//三个数求最小值 
	return min(x,min(y,z));
}
int check_row(int x,int y){//判断做哪一行，返回x和y两行中最优的 
	if(Row[x]>Row[y]){
		return x;
	}else if(Row[x]<Row[y]){
		return y;
	}
	if(Min(abs(x-1),abs(r+3-x),abs(r/2+2-x))<Min(abs(y-1),abs(r+3-y),abs(r/2+2-y))){
		return x;
	}else if(Min(abs(x-1),abs(r+3-x),abs(r/2+2-x))>Min(abs(y-1),abs(r+3-y),abs(r/2+2-y))){
		return y;
	}
	return min(x,y);
}
int check_line(int row){//判断做row行的哪一列，返回列数 
	if(a[row][5]=='-'&&a[row][7]!='-'){
		return 5;
	}
	if(a[row][7]=='-'&&a[row][5]!='-'){
		return 7;
	}
	if(a[row][5]=='-'&&a[row][7]=='-'){
		return (Left<=Right?5:7);
	}
	//优先级1 
	if(a[row][3]=='-'&&a[row][9]!='-'){
		return 3;
	}
	if(a[row][9]=='-'&&a[row][3]!='-'){
		return 9;
	}
	if(a[row][3]=='-'&&a[row][9]=='-'){
		return (Left<=Right?3:9);
	}
	//优先级2 
	if(a[row][1]=='-'&&a[row][11]!='-'){
		return 1;
	}
	if(a[row][11]=='-'&&a[row][1]!='-'){
		return 11;
	}
	if(a[row][1]=='-'&&a[row][11]=='-'){
		return ((Left<=Right)?1:11);
	}
	//优先级3 
	if(a[row][6]=='-'){
		return 6;
	}
	//优先级4 
	if(a[row][2]=='-'&&a[row][10]!='-'){
		return 2;
	}
	if(a[row][10]=='-'&&a[row][2]!='-'){
		return 7;
	}
	if(a[row][2]=='-'&&a[row][10]=='-'){
		return (Left<=Right?2:10);
	}
	//优先级5 
}
int main(){
	scanf("%d%d",&r,&n);
	Row[0]=Row[1]=Row[r/2+2]=Row[r+3]=-inf;//初始化 
	for(int i=1;i<=r+3;i++){
		for(int j=1;j<=11;j++){
			cin>>a[i][j];
			if(a[i][j]=='#'){
				//平衡 
				if(j<6){
					Left+=1;
				}
				if(i>6){
					Right+=1;
				}
			}
			if(a[i][j]=='-'){
				Row[i]+=1;
			}
		}
	}
	while(n--){
		//确定行数 
		int door=check_door(),row;
		if(door){
			row=door;
		}else{
			maxidx=0;
			for(int i=1;i<=n;i++){
				maxidx=check_row(i,maxidx);
			}
			row=maxidx;
		}
		//确定列数 
		int line=check_line(row);
		a[row][line]=++now;
		Row[row]-=1;
		if(line<6){
			Left+=1;
		}
		if(line>6){
			Right+=1;
		}
	}
	//输出 
	for(int i=1;i<=r+3;i++){
		for(int j=1;j<=11;j++){
			cout<<a[i][j];
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

很明显，我们可以用模拟来解决。

具体思路如下：

1. 首先，读取输入数据，包括座位排数 $r$、购票乘客数 $n$，以及飞机的当前布局。

2. 对于每个乘客，按照以下步骤为其分配座位：

   - 首先，检查是否有出口行后面有空座位的情况。如果有，则忽略其他排，在最后一步平衡飞机时再考虑它们。
   
   - 在剩下的排中，选择空座位最多的一排座位。如果有多个符合条件的排，选择距离最近的出口行最近的排。如果仍有多个符合条件的排，选择编号最低的排。
   
   - 在所选的排中，按照优先级选择一个空座位给乘客。优先级从高到低排序如下：
   
     - 中间组的过道座位（即 `D` 或 `F`）
     
     - 第一组和第三组的过道座位（即 `C` 或 `G`）
     
     - 靠窗座位（即 `A` 或 `I`）
     
     - 中间组中的中间座位（即 `E`）
     
     - 第一组和第三组的中间座位（即 `B` 或 `H`）
     
   - 如果有多个空座位具有相同的最高优先级，考虑整个飞机平衡的情况。选择空座位较多的一侧，如果两侧空座位相同，则选择飞机左侧的座位。
   - 将所选的座位标记为已占用。
   
3. 输出最终的飞机布局。

### 完整代码：

```cpp
#include <iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

char Map[55][55];
int seat[55];
int d[55];
int r,n;
int row;
int lef;
int righ;

void getrow(){
   if(seat[2]&&seat[r/2+3]){
     if(seat[2]==seat[r/2+3]||seat[2]>seat[r/2+3]) row=2;
     else row=r/2+3;
   }
   else if(seat[2]) row=2;
   else if(seat[r/2+3]) row=r/2+3;
   else{
      int maxseat=0;
      for(int i=1;i<=r+3;i++) maxseat=max(maxseat,seat[i]);
      int mind=100;
      for(int i=1;i<=r+3;i++) if(seat[i]==maxseat) mind=min(mind,d[i]);
      for(int i=1;i<=r+3;i++) if(seat[i]==maxseat&&d[i]==mind) {row=i; break;}
   }
}

void getseat(char c){
   seat[row]--;
   if(Map[row][5]=='-'&&Map[row][7]=='-'){
      if(lef>righ) {Map[row][7]=c; righ++; return;}
      else {Map[row][5]=c; lef++; return;}
   }
   else if(Map[row][5]=='-') {Map[row][5]=c; lef++; return;}
   else if(Map[row][7]=='-') {Map[row][7]=c; righ++; return;}
   if(Map[row][3]=='-'&&Map[row][9]=='-'){
      if(lef>righ) {Map[row][9]=c; righ++; return;}
      else {Map[row][3]=c; lef++; return;}
   }
   else if(Map[row][3]=='-') {Map[row][3]=c; lef++; return;}
   else if(Map[row][9]=='-') {Map[row][9]=c; righ++; return;}
   if(Map[row][1]=='-'&&Map[row][11]=='-'){
      if(lef>righ) {Map[row][11]=c; righ++; return;}
      else {Map[row][1]=c; lef++; return;}
   }
   else if(Map[row][1]=='-') {Map[row][1]=c; lef++; return;}
   else if(Map[row][11]=='-') {Map[row][11]=c; righ++; return;}
   if(Map[row][6]=='-') {Map[row][6]=c; return;}
   if(Map[row][2]=='-'&&Map[row][10]=='-'){
      if(lef>righ) {Map[row][10]=c; righ++; return;}
      else {Map[row][2]=c; lef++; return;}
   }
   else if(Map[row][2]=='-') {Map[row][2]=c; lef++; return;}
   else if(Map[row][10]=='-') {Map[row][10]=c; righ++; return;}
}

int main()
{
    scanf("%d%d",&r,&n);
    for(int i=1;i<=r+3;i++){
        for(int j=1;j<=11;j++){
            scanf(" %c",&Map[i][j]);
            if(Map[i][j]=='-') seat[i]++;
            if(Map[i][j]=='#'){
                if(j<6) lef++;
                if(j>6) righ++;
            }
        }
        d[i]=min(abs(i-1),min(abs(i-r/2-2),abs(i-r-3)));//i分别到1,r/2+2,r+3的距离。到r+3的距离我竟然写成了abs(i-r)...
    }
    for(int i=0;i<n;i++){
        char c='a'+i;
        getrow();
        getseat(c);

    }
    for(int i=1;i<=r+3;i++){
        for(int j=1;j<=11;j++){
            cout<<Map[i][j];
        }
        printf("\n");
    }
    return 0;
}
```


---

## 作者：Maysoul (赞：0)

**果然心情不好就得写模拟！**

非常显然，这是一道模拟题。

题面就不赘述了，我们直接看排序规则。

规则分为两类，行规则和座规则。

行规则如下：

1. 如果出口排后面没坐满，先选择出口排后面。

2. 当 $ 1 $ 不满足时，选择空座位最多的一排。

3. 当 $ 2 $ 有多个时，选择最靠近出口的一排。

4. 当 $ 3 $ 有多个时，选择编号最低的一排。

模拟题最重要的是把这个过程模拟出来，故我们须使用一个数组记录每一排的人数，然后先观察出口排后面，如果都坐满了就循环一遍找出人数最小的排。中间只需考虑空座位数量相等的时候，再去比较它们与出口的距离。

考虑完行规则，再考虑座规则：

1. 按照题意给出的座位优先级处理。

2. 如果优先级相等的两个座位都空着，就选择**使飞机重量平衡的一端**。

3. 如果飞机重量平衡，则选择左边的。

这个使飞机重量平衡看似比较难理解，但我们只需要两个变量来统计左边和右边的人数即可，如果两个座位都空着那么就选择人数小的那一边。

代码里还有很多小细节：

```
//2023/5/14
//别着急，先通读一遍题目
//别忘了开long long
//写完先看一遍怎么降复杂度
//要么开全局变量要么给定初值
//想想看，有什么情况需要特判
//看看数组开的够不够大
//std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
int num,ans,len;
int r,n,l,ri;
char a[60][15];//用来存图
int full[60];//记录每一排的人数
int getmin()
{
	int minn=MAXN;
	int p=0;
	for (int i=1;i<=r+3;i++)
	{
		if(i!=1&&i!=r/2+2&&i!=r+3)
		{
			if(full[i]<minn)
			{
				minn=full[i];
				p=i;
			}
			if(full[i]==minn)
			{
				int baka=min(abs(p-1),min(abs(p-(r/2+2)),abs(p-(r+3))));
				int hentai=min(abs(i-1),min(abs(i-(r/2+2)),abs(i-(r+3))));
				if(baka>hentai)//这个看起来吓人，但实际上就是得到了这一排离离他最近的出口的距离
				{
					minn=full[i];
					p=i;
				}
			}
		}
	}
	return p;
}
int hanglevel()
{
	int op=min(full[2],full[r/2+3]);//先观察出口排后方
	if(op==full[2]&&op<9) return 2;
	if(op==full[r/2+3]&&op<9) return r/2+3;
	return getmin();
}
bool seat(int x,int y,int p,int i)
{
	//cout<<a[p][x]<<" "<<a[p][y]<<endl;
	if(a[p][x]=='-'&&a[p][y]=='-')//都没坐满
	{
		if(l<=ri) //调节平衡
		{
			a[p][x]=i-1+'a'; 
			l++;
		}
		else 
		{ 
			a[p][y]=i-1+'a'; 
			ri++;
		}
		full[p]++;
		return 1;
	}
	if(a[p][x]=='-')
	{
		a[p][x]=i-1+'a'; 
		if(x!=6) l++;//把这些情况统筹起来处理的时候，一定要记住有一种情况是既不在左也不在右的
		full[p]++;
		return 1;
	}
	if(a[p][y]=='-')
	{
		a[p][y]=i-1+'a'; 
		ri++;
		full[p]++;
		return 1;
	}
	return 0;
}
int main()
{
	cin>>r>>n;
	len=r+3;
	for (int i=1;i<=len;i++)
	{
		for (int j=1;j<=11;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='#')
			{
				if(j<6) l++;//这里把人分成左边和右边
				if(j>6) ri++;
				full[i]++;
			}
		}
	}
	for (int i=1;i<=n;i++)
	{
		int p=hanglevel();
		//cout<<p<<endl;
		if(seat(5,7,p,i)) continue;//这里我用了一个偷懒的方式，直接把两个座位传入函数就省的挨个模拟
		if(seat(3,9,p,i)) continue;
		if(seat(1,11,p,i)) continue;
		if(seat(6,0,p,i)) continue;
		seat(2,10,p,i);
	}
	for (int i=1;i<=len;i++)
	{
		for (int j=1;j<=11;j++)
		{
			cout<<a[i][j];
		}
		cout<<endl;
	}
	return 0;
}

```


---

