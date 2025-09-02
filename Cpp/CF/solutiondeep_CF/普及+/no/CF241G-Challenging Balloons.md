# 题目信息

# Challenging Balloons

## 题目描述

Martha — as a professional problemsetter — proposed a problem for a world-class contest. This is the problem statement:

Tomorrow is Nadia's birthday, and Bardia (her brother) is assigned to make the balloons ready!

There are $ n $ balloons (initially empty) that are tied to a straight line on certain positions $ x_{1},x_{2},...,x_{n} $ . Bardia inflates the balloons from left to right. As a result, $ i $ -th balloon gets bigger and bigger until its radius reaches the pressure endurance $ p_{i} $ or it touches another previously-inflated balloon.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF241G/ad76c1ea81bca8ad7b086e9e6da5329cfb0428b0.png)While Bardia was busy with the balloons, he wondered "What will be the sum of radius of balloons after all of the balloons are inflated?". Being a nerdy type of guy, he is now thinking about the problem instead of preparing his sister's birthday. Calculate the answer to Bardia's problem so that Nadia's birthday won't be balloon-less.

Artha — Martha's student — claimed his solution got accepted. Martha (being his teacher for a long time!) knew he couldn't have solved the problem for real and thus thinks there is something wrong with the testcases. Artha isn't anyhow logical, which means there is no way for Martha to explain the wrong point in his algorithm. So, the only way is to find a testcase to prove him wrong!

Artha's pseudo-code is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF241G/6e961f208c0c9a0d7488024c73cdaa09ded78277.png)You should output a small testcase for the problem such that Artha's algorithm is incorrect. The algorithm's output is considered correct if it differs from the correct value by no more than 1.

## 说明/提示

The testcase depicted in the figure above (just showing how output should be formatted):

`<br></br>4<br></br>0 9<br></br>6 3<br></br>12 7<br></br>17 1<br></br>`

# AI分析结果

### 题目内容
# 具有挑战性的气球

## 题目描述
玛莎——作为一名专业的出题人——为一场世界级竞赛出了一道题。题目如下：

明天是娜迪娅的生日，巴迪亚（她的哥哥）负责准备气球！

有 $n$ 个气球（初始为空）系在一条直线上的特定位置 $x_{1},x_{2},\ldots,x_{n}$ 。巴迪亚从左到右给气球充气。结果是，第 $i$ 个气球会越来越大，直到其半径达到耐压值 $p_{i}$ 或者碰到另一个之前充好气的气球。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF241G/ad76c1ea81bca8ad7b086e9e6da5329cfb0428b0.png)当巴迪亚忙于处理气球时，他想到“所有气球都充好气后，气球半径的总和会是多少呢？”。作为一个书呆子类型的人，他现在正在思考这个问题而不是准备他妹妹的生日。计算出巴迪亚问题的答案，这样娜迪娅的生日就不会没有气球了。

阿尔塔——玛莎的学生——声称他的解决方案通过了。玛莎（作为他的老师很长时间了！）知道他不可能真正解决这个问题，因此认为测试用例有问题。阿尔塔一点都不讲逻辑，这意味着玛莎没办法向他解释其算法中的错误点。所以，唯一的办法就是找到一个测试用例来证明他是错的！

阿尔塔的伪代码如下所示：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF241G/6e961f208c0c9a0d7488024c73cdaa09ded78277.png)你应该为这个问题输出一个小的测试用例，使得阿尔塔的算法不正确。如果算法的输出与正确值的差异不超过1，则认为该算法的输出是正确的。

## 说明/提示
上图所示的测试用例（仅展示输出格式）：

`<br></br>4<br></br>0 9<br></br>6 3<br></br>12 7<br></br>17 1<br></br>`

### 算法分类
构造

### 综合分析与结论
该题要求构造一个测试用例，证明给定伪代码算法不正确。题解通过分析伪代码仅检查前面300个气球的特点，构造出302个气球的测试用例。其中第一个和最后一个气球半径限度大且位置远，中间300个气球半径限度递减且间距足够，避免气球提前相撞和被清理，以此使伪代码算法出错。

### 所选的题解
 - **作者：FFTotoro（5星）**
    - **关键亮点**：清晰分析伪代码缺陷，巧妙构造出针对性测试用例，代码实现包含测试函数与SPJ，逻辑完整。
    - **个人心得**：无

### 重点代码及核心实现思想
```cpp
// 伪代码中的函数，调换 l 的值可以测试正确和错误的代码
double solve(vector<pii> a,int l){
  double c=0;
  vector<double> r(a.size());
  vector<int> s;
  for(int i=0;i<a.size();i++){
    r[i]=a[i].second;
    for(int j=0;j<min((int)s.size(),l);j++){
      double t=s[s.size()-j-1];
      r[i]=min(r[i],pow(a[i].first-a[t].first,2)/r[t]/4);
    }
    while(!s.empty()&&r[s.back()]<=r[i])s.pop_back();
    s.emplace_back(i),c+=r[i];
  }
  return c;
} 
bool spj(vector<pii> a){
  return solve(a,a.size())!=solve(a,300);
}
int main(){
  ios::sync_with_stdio(false);
  vector<pii> a(302);
  a[0]=make_pair(1,1e6);
  for(int i=1;i<=300;i++)
    a[i]=make_pair(3e5+i*600,300-i+1);
  a[301]=make_pair(1e6,1e6);
  if(spj(a)){
    cout<<"302\n";
    for(auto [x,y]:a)
      cout<<x<<' '<<y<<endl;
  }
  else cout<<"Wrong Answer!\n";
  return 0;
}
```
核心实现思想：`solve`函数模拟伪代码算法计算气球半径总和，`spj`函数通过对比正常计算（检查所有气球）和按伪代码限制（只检查300个气球）的结果来判断测试用例是否有效。`main`函数构造特定的302个气球数据，并调用`spj`函数输出测试用例。 

### 最优关键思路或技巧
通过分析伪代码的局限性，利用其对气球检查数量的限制，巧妙构造特殊数据分布的气球位置和半径限度，使算法出现错误。

### 可拓展之处
同类型题可关注构造类题目，通常需要根据给定条件或算法缺陷，构造出符合要求的数据。类似套路是深入分析给定算法的边界条件、特殊情况等，针对性构造数据。

### 洛谷推荐题目
 - [P1338 末日的传说](https://www.luogu.com.cn/problem/P1338)
 - [P2676 [USACO07DEC]Bookshelf B](https://www.luogu.com.cn/problem/P2676)
 - [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)

---
处理用时：45.81秒