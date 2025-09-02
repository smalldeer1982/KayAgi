# 题目信息

# Vanya and Exams

## 题目描述

Vanya wants to pass $ n $ exams and get the academic scholarship. He will get the scholarship if the average grade mark for all the exams is at least $ avg $ . The exam grade cannot exceed $ r $ . Vanya has passed the exams and got grade $ a_{i} $ for the $ i $ -th exam. To increase the grade for the $ i $ -th exam by 1 point, Vanya must write $ b_{i} $ essays. He can raise the exam grade multiple times.

What is the minimum number of essays that Vanya needs to write to get scholarship?

## 说明/提示

In the first sample Vanya can write 2 essays for the 3rd exam to raise his grade by 2 points and 2 essays for the 4th exam to raise his grade by 1 point.

In the second sample, Vanya doesn't need to write any essays as his general point average already is above average.

## 样例 #1

### 输入

```
5 5 4
5 2
4 7
3 1
3 2
2 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 5 4
5 2
5 2
```

### 输出

```
0
```

# AI分析结果

### 题目内容
#### Vanya和考试
#### 题目描述
Vanya想要通过n场考试并获得学术奖学金。如果所有考试的平均成绩至少为avg，他就能获得奖学金。考试成绩不能超过r。Vanya已经参加了考试，第i场考试的成绩为ai。为了将第i场考试的成绩提高1分，Vanya必须写bi篇论文。他可以多次提高考试成绩。

Vanya获得奖学金所需写的最少论文数量是多少？

#### 说明/提示
在第一个样例中，Vanya可以为第3场考试写2篇论文，将成绩提高2分，为第4场考试写2篇论文，将成绩提高1分。

在第二个样例中，Vanya不需要写任何论文，因为他的总平均成绩已经高于平均水平。

#### 样例 #1
**输入**
```
5 5 4
5 2
4 7
3 1
3 2
2 5
```
**输出**
```
4
```
#### 样例 #2
**输入**
```
2 5 4
5 2
5 2
```
**输出**
```
0
```
• **算法分类**：贪心
• **综合分析与结论**：这些题解都采用贪心算法解决问题，核心思路是按每提高1分所需论文数（bi）从小到大排序各学科，优先从最易提分的学科开始提升成绩，直至平均成绩达到要求。各题解都关注到了总分特判（若初始总分已达要求则输出0）和单科成绩上限（不能超过r）的要点。不同之处主要体现在代码实现细节，如排序方式、循环写法、变量命名等。
• **所选的题解**：
  - **作者：donotctjuntilAFO (5星)**
    - **关键亮点**：代码简洁清晰，使用C++标准库，结构体重载小于号实现排序，逻辑严谨，对总分的处理巧妙，先计算出目标总分并在输入时就进行判断。
    - **重点代码**：
```cpp
struct node{
    LL a,b;
    bool operator<(const node &x){
        return this->b<x.b;
    }
}t[100005];
// 核心实现思想：定义结构体存储每场考试的成绩a和提分1分所需论文数b，重载小于号以便使用sort函数按b从小到大排序。
int main(){
    scanf("%lld%lld%lld",&n,&r,&avg);
    cur=n*avg;
    f(i,1,n){
        scanf("%lld%lld",&t[i].a,&t[i].b);
        if(cur>t[i].a){
            cur-=t[i].a;
        }
        else{
            printf("0");
            return 0;
        }
    }
    sort(t+1,t+n+1);
    LL now=1;
    while(cur>=r-t[now].a&&now<=n){
        ans+=(r-t[now].a)*t[now].b;
        cur-=r-t[now].a;
        now++;
    }
    ans+=cur*t[now].b;
    printf("%lld",ans);
    return 0;
}
// 核心实现思想：先计算目标总分cur，输入成绩时判断是否已达目标，若未达则按b排序后，从最易提分科目开始提升，直至总分达标。
```
  - **作者：YanYou (4星)**
    - **关键亮点**：思路清晰，在博客中给出详细说明，代码使用Pascal语言，快排实现了按所需论文数排序，对总分的计算和处理也较为清晰。
    - **重点代码**：
```pascal
procedure sort(l,r:longint);//快排（P党的悲催啊）
var i,j,m1,m2,t:longint;
begin
  i:=l; j:=r; m1:=b[(l+r) shr 1]; m2:=a[(l+r) shr 1];
  repeat
    while (b[i]<m1)or(b[i]=m1)and(a[i]<m2) do inc(i);
    while (m1<b[j])or(m1=b[j])and(m2<a[j]) do dec(j);
    if i<=j then begin
      t:=a[i]; a[i]:=a[j]; a[j]:=t;
      t:=b[i]; b[i]:=b[j]; b[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
end;
// 核心实现思想：快排按每提高1分所需论文数b排序，若b相同则按原成绩a排序。
begin
  readln(n,m,ave); s:=n*ave;
  for i:=1 to n do begin
    readln(a[i],b[i]);
    dec(s,a[i]);
  end;
  if s=0 then begin writeln(0); exit; end;//判断是否需要写论文
  sort(1,n);
  i:=1;
  while s>0 do begin
    if m-a[i]<=s then inc(ans,b[i]*(m-a[i]))
    else inc(ans,s*b[i]);//尽量写代价低的（即得一分需写的论文少的）
    dec(s,(m-a[i]));
    inc(i);
  end;
  writeln(ans);
end.
// 核心实现思想：计算目标总分s，输入成绩时减去已得分数，排序后从最易提分科目开始提升，直至总分达标。
```
  - **作者：NotNaLocker (4星)**
    - **关键亮点**：代码注释详细，对排序规则和模拟写论文过程解释清晰，结构体排序实现清晰明了，对边界情况的处理也很得当。
    - **重点代码**：
```cpp
bool cmp(subject a,subject b){
	if(a.b<b.b) return 1;
	else if(a.b==b.b&&a.a>b.a) return 1;
	else return 0;
}
// 核心实现思想：定义排序规则，先按每提高1分所需论文数b从小到大排序，若b相同则按原成绩a从大到小排序。
int i=1;
while(sum<avg*n){
	if(avg*n-sum>r-vanya[i].a){   //学分仍然不够达到要求，就加学分，同时累计sum。
		ans+=vanya[i].b*(r-vanya[i].a);   //注意，这里要乘以论文数，如果直接加的话那论文数这个值就没什么用了。
		sum+=r-vanya[i].a;
		i++;
	}
	else{   //最后一次，直接加完学分后退出循环。
		ans+=vanya[i].b*(avg*n-sum);
		break;
	}
}
// 核心实现思想：通过循环模拟写论文过程，从最易提分科目开始，判断每次提分能否达到目标总分，相应更新总分sum和论文数ans。
```
• **最优关键思路或技巧**：采用贪心策略，按每提高1分所需论文数对考试科目进行排序，优先处理最易提分的科目，这样能保证在每一步选择中都使论文总数最少。在实现过程中，提前计算目标总分并在输入时进行判断，减少不必要的计算；在循环提分过程中，合理判断剩余学分与单科可提学分的关系，准确计算论文数。
• **可拓展之处**：同类型题可涉及各种资源分配场景，要求以最小代价达到某个目标，类似算法套路都是按代价从小到大排序资源，逐步分配资源以满足目标。
• **推荐洛谷题目**：
  - P1090 [合并果子](https://www.luogu.com.cn/problem/P1090)，通过合并果子的操作，以最小的总代价完成合并，考察贪心策略。
  - P1199 [三国游戏](https://www.luogu.com.cn/problem/P1199)，在游戏场景中选择武将使自己得分最高，需要运用贪心思想。
  - P1223 排队接水，通过安排接水顺序使所有人等待时间总和最小，也是典型的贪心问题。 

---
处理用时：79.79秒