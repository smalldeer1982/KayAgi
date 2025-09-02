---
title: "ツカモの栽培"
layout: "post"
diff: 难度0
pid: AT_future_contest_2018_final_a
tag: []
---

# ツカモの栽培

## 题目描述

[problemUrl]: https://atcoder.jp/contests/future-contest-2018-final/tasks/future_contest_2018_final_a

高橋君は、新たな惑星を発見しました。この惑星では、植物「ツカモ」がよく育つことが分かっています。ツカモを出来るだけ多く育てましょう！

この惑星は、$ 50×50 $のマス目で表されます。左から $ x $ 番目、上から $ y $ 番目のマスが $ (x,y) $ です。左上のマスが $ (1,1) $、右上のマスが $ (50,1) $、右下のマスが $ (50,50) $ です。 マスは、以下の $ 5 $ 種類で構成されています。

- 更地：何もない土地です。ツカモが生えると畑になります。
- 畑：ツカモが生えている土地です。ツカモは、$ 1 $ 本から $ 99 $ 本生えています。
- 岩：岩です。これがあるとツカモの繁殖が出来ず、また、移動コストも大きくなります。
- ワープゲート： 高橋君が、地球からこの惑星に来る時に使います。最初は必ず $ 1 $ つだけ存在します。
- 道路： ワープゲートから、高橋君が移動するために使う道です。移動コストが小さいです。

高橋君は、$ 2 $ つのパラメータを持っています。

- お金： 道路やワープゲートの作成、更地化、労働力のアップに使います。収穫とアルバイトで増えます。初期値は $ 100 $ です。お金は次のターンに引き継がれます。
- 労働力： 高橋君が一度にツカモを収穫できる量の計算に使います。初期値は $ 100 $ で、労働力のアップで増やすことが可能です。労働力を消費しても、次のターンには回復します。

ツカモは、以下のような特性を持っています。

- ツカモが同じマスに $ 100 $ 本揃った瞬間、そのマスのツカモは全て岩になる。
- あるマスについて、そのマスが更地もしくは畑であり、そのマス自身か上下左右に隣り合うマスが畑である場合、そのマスの次のターンのツカモは $ 1 $ 本増加する。岩はツカモに含めない。

高橋君には、$ 1000 $ ターンの開発期間が与えられます。この $ 1000 $ターンの間に、出来るだけ多くのツカモを収穫したいです。 高橋君の $ 1000 $ ターンの出力をしてください。 高橋君が出来る行動は、以下の $ 7 $ つのうち、どれか $ 1 $ つです。

 入力ファイル：

 

   
 出力ファイル：

 

   
  
  ▶ 再生速度: 遅速 

    turn 

 

  









































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































 

Score

0

 

ツカモ

0

 

おかね

100

 

労働力

100 / 100

 

 

 

 
  var inputFlg = false;
  var loadedFlg = false;
  const N = 50;
  const TURN = 1000;
  var outputData = [];
  // パラメータ
  var datalist = [...Array(TURN+1)].map(() => [...Array(N)].map(() => [...Array(N)].map(() => 0)));
  var tsukammo = [...Array(TURN+1)].map(() => 0);
  var money = [...Array(TURN+1)].map(() => 100);
  var work = [...Array(TURN+1)].map(() => 100);
  var maxWork = [...Array(TURN+1)].map(() => 100);
  // for simulate
  var dx = [1,0,-1,0];
  var dy = [0,1,0,-1];

  // 入力ファイルの読込
  var handleInputFiles = function (file, callback) {
    loadedFlg = false;
    document.getElementById('score').innerText = 0;
    var reader = new FileReader();
    reader.readAsText(file[0]);
    reader.onload = function (ev) {
      const inputDatalist = reader.result.split("\n");
      if(inputDatalist.length &lt; N){
        console.log("N error!! " + inputDatalist.length);
        document.getElementById('inputFile').innerText = 'error!';
        return;
      }
      for (var i = 0; i &lt; N; i++) {
        if(inputDatalist[i].length !== N+1){
          console.log("N error!! " + inputDatalist[i].length);
          console.log(inputDatalist[i]);
          document.getElementById('inputFile').innerText = 'error!';
          return;
        }
        for (var j = 0; j &lt; N; j++) {
          switch(inputDatalist[i].charAt(j)){
            case ".":
              datalist[0][i][j] = 0;
              break;
            case "#":
              datalist[0][i][j] = 100;
              break;
            case "W":
              datalist[0][i][j] = 200;
              break;
            default:
              document.getElementById('inputFile').innerText = 'error!';
              console.log("error!!");
              return;
          }
        }
      }
    };
    console.log(datalist);
    document.getElementById('inputFile').innerText = 'OK!';
    console.log("input OK!");
    inputFlg = true;
    setTimeout(function() {
      //callback(datalist[0]);
      callback(0);
    }, 50);
  }

  // 出力ファイルの読込
  function handleOutputFiles(file) {
    loadedFlg = false;
    outputData = [];
    document.getElementById('score').innerText = 0;
    var reader = new FileReader();
    reader.readAsText(file[0]);
    reader.onload = function (ev) {
      const outputDatalist = reader.result.split("\n");
      if(outputDatalist.length &lt; TURN){
        console.log("output filr error!");
        document.getElementById('outputFile').innerText = 'error!';
        return;
      }
      for (var i = 0; i &lt; TURN; i++) {
        var row = []
        var tmp = outputDatalist[i].split(' ');
        row.push(tmp[0]);
        for(var j = 1; j &lt; tmp.length; j++){
          row.push(Number(tmp[j]));
        }
        outputData.push(row);
      }
    }
    console.log(outputData);
    document.getElementById('outputFile').innerText = 'OK!';
    console.log("output OK!");
  }
  
  // Queue
  function Queue() {
    this.__a = new Array();
  }

  Queue.prototype.enqueue = function(o) {
    this.__a.push(o);
  }

  Queue.prototype.dequeue = function() {
    if( this.__a.length > 0 ) {
      return this.__a.shift();
    }
    return null;
  }

  Queue.prototype.size = function() {
    return this.__a.length;
  }
  
  function calcCost(t) {
    var cost = [...Array(N)].map(() => [...Array(N)].map(() => Number.MAX_SAFE_INTEGER));
    var q = new Queue();
    // 各ワープゲートから最短コストを算出
    for (var i = 0; i &lt; N; i++) {
      for (var j = 0; j &lt; N; j++) { 
        if(datalist[t][i][j] === 200){
          cost[i][j] = 0;
          q.enqueue([j, i]);
        }
      }
    }
    while( p = q.dequeue()) {
      var nowCost = cost[p[1]][p[0]];
      for(var d = 0; d &lt; 4; d++){
        var nx = p[0] + dx[d];
        var ny = p[1] + dy[d];
        
        if(outMap(nx,ny)){
          continue;
        }
        var nextCost = nowCost;
        if(datalist[t][ny][nx] === 100){
          nextCost += 50;
        }else if(datalist[t][ny][nx] === 300){
          nextCost += 1;
        }else{
          nextCost += 10;
        }
        if(cost[ny][nx] > nextCost){
          cost[ny][nx] = nextCost;
          q.enqueue([nx, ny]);
        }
      }
    }
    return cost;
  }
  
  // シミュレート
  function simulate() {
    // 初期設定
    var cost = [];
    tsukammo[0] = 0;
    money[0] = 100;
    work[0] = 100;
    maxWork[0] = 100;
    var doneMap = [...Array(N)].map(() => [...Array(N)].map(() => 0));
    // 前ターンの盤面をコピー
    for (var i = 0; i &lt; N; i++) {
      for (var j = 0; j &lt; N; j++) { 
        datalist[1][i][j] = datalist[0][i][j];
      }
    }
    // outputの反映
    for (var t = 1; t &lt;= TURN; t++) {
      doneMap = [...Array(N)].map(() => [...Array(N)].map(() => 0));
      // var tarY = Math.floor(Math.random()*N);
      // var tarX = Math.floor(Math.random()*N);
      // datalist[t+1][tarY][tarX] = [0, 1, 100, 200, 300][Math.floor(Math.random()*5)];
      // 前のターンの値をコピー
      tsukammo[t] = tsukammo[t-1];
      money[t] = money[t-1];
      maxWork[t] = maxWork[t-1];
      work[t] = maxWork[t];
      // TODO このターンの出力を反映
      switch(outputData[t-1][0]){
        case "warpgate":
          if(outputData[t-1].length !== 3){
            wrongAnswer(outputData[t-1][0], t);
            return;
          }
          var x = outputData[t-1][1]-1;
          var y = outputData[t-1][2]-1;
          var pay = 1000;
          if(money[t] >= pay && (datalist[t][y][x] !== 100 && datalist[t][y][x] !== 200)){
            money[t] -= pay;
            datalist[t][y][x] = 200;
          }
          break;
        case "plant":
          if(outputData[t-1].length !== 3){
            wrongAnswer(outputData[t-1][0], t);
            return;
          }
          var x = outputData[t-1][1]-1;
          var y = outputData[t-1][2]-1;
          if(datalist[t][y][x] === 0){
            datalist[t][y][x] = 2;
            // 既に伝搬済の状態
            for(var d = 0; d &lt; 4; d++){
              var nx = x + dx[d];
              var ny = y + dy[d];
              if(outMap(nx,ny)){
                continue;
              }
              if(datalist[t][ny][nx] === 0){
                datalist[t][ny][nx] = 1;
              }
            }
          }else if(datalist[t][y][x] > 0 && datalist[t][y][x] &lt; 100){
            datalist[t][y][x]++;
          }
          break;
        case "destroy":
          if(outputData[t-1].length !== 5 || outputData[t-1][1] > outputData[t-1][3] || outputData[t-1][2] > outputData[t-1][4]){
            wrongAnswer(outputData[t-1][0], t);
            return;
          }
          cost = calcCost(t-1);
          for(var y = outputData[t-1][2] -1; y &lt; outputData[t-1][4]; y++){
            for(var x = outputData[t-1][1] -1; x &lt; outputData[t-1][3]; x++){
              if((datalist[t-1][y][x] > 0 && datalist[t-1][y][x] &lt;= 100) || datalist[t][y][x] === 300){
                // TODO コストの計算
                var c = Math.max(0, cost[y][x]);
                if(money[t] &lt; c){
                  continue;
                }
                money[t] -= c;
                datalist[t][y][x] = 0;
                // 変更したことを明示
                doneMap[y][x] = 1;
              }
            }
          }
          break;
        case "harvest":
          if(outputData[t-1].length !== 5 || outputData[t-1][1] > outputData[t-1][3] || outputData[t-1][2] > outputData[t-1][4]){
            wrongAnswer(outputData[t-1][0], t);
            return;
          }
          cost = calcCost(t-1);
          for(var y = outputData[t-1][2] -1; y &lt; outputData[t-1][4]; y++){
            for(var x = outputData[t-1][1] -1; x &lt; outputData[t-1][3]; x++){
              // 1ターン前の量を収穫
              if(datalist[t-1][y][x] > 0 && datalist[t-1][y][x] &lt; 100){
                // TODO コストの計算
                var c = Math.max(0, cost[y][x] - 10);
                if(work[t] &lt; c){
                  continue;
                }
                work[t] -= c;
                tsukammo[t] += datalist[t-1][y][x];
                money[t] += datalist[t-1][y][x];
                datalist[t][y][x] = 0;
                // 変更したことを明示
                doneMap[y][x] = 1;
              }
            }
          }
          break;
        case "road":
          if(outputData[t-1].length !== 5 || outputData[t-1][1] > outputData[t-1][3] || outputData[t-1][2] > outputData[t-1][4]){
            wrongAnswer(outputData[t-1][0], t);
            return;
          }
          if(outputData[t-1][1] !== outputData[t-1][3] && outputData[t-1][2] !== outputData[t-1][4]){
            wrongAnswer(outputData[t-1][0], t);
            return;
          }
          var long = 1 + Math.abs(outputData[t-1][1] - outputData[t-1][3]) + Math.abs(outputData[t-1][2] - outputData[t-1][4]);
          var pay = long * long;
          if(pay &lt;= money[t]){
            money[t] = money[t] - pay;
            if(outputData[t-1][1] === outputData[t-1][3]){
              var x = outputData[t-1][1]-1;
              var ny = outputData[t-1][2]-1;
              for (var i = 0; i &lt; long; i++) {
                if(datalist[t][ny][x] &lt; 100){
                  datalist[t][ny][x] = 300;
                  // 変更したことを明示
                  doneMap[ny][x] = 1;
                }
                ny++;
              }
            }else if(outputData[t-1][2] === outputData[t-1][4]){
              var nx = outputData[t-1][1]-1;
              var y = outputData[t-1][2]-1;
              for (var i = 0; i &lt; long; i++) {
                if(datalist[t][y][nx] &lt; 100){
                  datalist[t][y][nx] = 300;
                  // 変更したことを明示
                  doneMap[y][nx] = 1;
                }
                nx++;
              }
            }
          }
          break;
        case "growup":
          if(outputData[t-1].length !== 2){
            wrongAnswer(outputData[t-1][0], t);
            return;
          }
          var max = 0;
          for(var i=0; i &lt;= outputData[t-1][1]; i++){
            var tmp = i*i;
            if(tmp > money[t]){
              break;
            }
            max = i;
          }
          var pay = max*max;
          money[t] = money[t] - pay;
          maxWork[t] += max;
          break;
        default:
          if(outputData[t-1][0].indexOf("work") === 0){
            money[t]++;
            break;
          }
          wrongAnswer(outputData[t-1][0], t);
          return;
      }
      // ツカモの増殖
      for (var i = 0; i &lt; N; i++) {
        for (var j = 0; j &lt; N; j++) {
          var tmp = datalist[t][i][j];
          if(tmp &lt;= 0){
            for(var d = 0; d &lt; 4; d++){
              var nx = j + dx[d];
              var ny = i + dy[d];
              if(outMap(nx,ny)){
                //console.log("out");
                continue;
              }
              if(datalist[t-1][ny][nx] > 0 && datalist[t-1][ny][nx] &lt; 100 && doneMap[ny][nx] === 0){
                datalist[t][i][j] = 1;
              }
            }
          }
        }
      }
      // 次ターンに盤面をコピー
      if(t>=TURN){
        break;
      }
      for (var i = 0; i &lt; N; i++) {
        for (var j = 0; j &lt; N; j++) {
          var tmp = datalist[t][i][j];
          if(tmp>0 && tmp<100){
            tmp++;
            datalist[t+1][i][j] = tmp;
          }else if(tmp &lt; 0){
            tmp = 0;
            datalist[t][i][j] = 0;
          }
          datalist[t+1][i][j] = tmp;
        }
      }
    }
    document.getElementById('score').innerText = tsukammo[TURN];
    loadedFlg = true;
  }
  
  
  function wrongAnswer(str, t) {
    console.log("simulate error!! turn="+ t + " "  + str);
    outputData = [];
    loadedFlg = false;
    _isRunning = false;
    start.innerText = '▶';
    renderMap(t);
    document.getElementById('slider1o').value = t;
    document.getElementById('outputFile').innerText = 'error!';
    document.getElementById('score').innerText = 'WA';
  }
  
  function outMap(x,y) {
    if(x >= 0 && x &lt; N && y >= 0 && y &lt; N){
      return false;
    }
    return true;
  }
  
  function removeClass(tarId) {
    document.getElementById(tarId).classList.remove("sarati");
    document.getElementById(tarId).classList.remove("hatake00");
    document.getElementById(tarId).classList.remove("hatake0");
    document.getElementById(tarId).classList.remove("hatake1");
    document.getElementById(tarId).classList.remove("hatake2");
    document.getElementById(tarId).classList.remove("hatake3");
    document.getElementById(tarId).classList.remove("iwa");
    document.getElementById(tarId).classList.remove("warp");
    document.getElementById(tarId).classList.remove("douro");
  }
  
  var renderMap = function(rendTurn) {
    
    if(!inputFlg){
      return;
    }
    //console.log("render")
    //console.log(data)
    document.getElementById('tsukammo').innerText = tsukammo[rendTurn];
    document.getElementById('money').innerText = money[rendTurn];
    document.getElementById('work').innerText = work[rendTurn] + " / " + maxWork[rendTurn];
    let dataIndex = 0;
    datalist[rendTurn].map((row, k) => {
      row.map((item, i) => {
        var tarId = 'map_' + String(dataIndex).padStart(4, '0');
        
        switch(item){
          case 0:
            document.getElementById(tarId).setAttribute('data-val', '更地');
            if(document.getElementById(tarId).className  !== 'sarati'){
              removeClass(tarId);
              document.getElementById(tarId).classList.add("sarati");
            }
            break;
          case 100:
            document.getElementById(tarId).setAttribute('data-val', '岩');
            if(document.getElementById(tarId).className  !== 'iwa'){
              removeClass(tarId);
              document.getElementById(tarId).classList.add("iwa");
            }
            break;
          case 200:
            document.getElementById(tarId).setAttribute('data-val', 'ワープゲート');
            if(document.getElementById(tarId).className  !== 'warp'){
              removeClass(tarId);
              document.getElementById(tarId).classList.add("warp");
            }
            break;
          case 300:
            document.getElementById(tarId).setAttribute('data-val', '道路');
            if(document.getElementById(tarId).className  !== 'douro'){
              removeClass(tarId);
              document.getElementById(tarId).classList.add("douro");
            }
            break;
          default:
            if(item > 0 && item &lt; 100) {
              document.getElementById(tarId).setAttribute('data-val', '畑='+item);
              if (item === 1) {
                removeClass(tarId);
                document.getElementById(tarId).classList.add("hatake00");
              }else if (item &lt; 10 && item > 1) {
                if(document.getElementById(tarId).className !== 'hatake0') {
                   removeClass(tarId);
                   document.getElementById(tarId).classList.add("hatake0");
                }
              } else if (item &lt; 30) {
                if(document.getElementById(tarId).className  !== 'hatake1') {
                  removeClass(tarId);
                  document.getElementById(tarId).classList.add("hatake1");
                }
              } else if (item &lt; 70) {
                if(document.getElementById(tarId).className  !== 'hatake2') {
                  removeClass(tarId);
                  document.getElementById(tarId).classList.add("hatake2");
                }
              } else {
                if(document.getElementById(tarId).className  !== 'hatake3') {
                  removeClass(tarId);
                  document.getElementById(tarId).classList.add("hatake3");
                }
              }
            } else {
              removeClass(tarId);
              console.log("error!! " + item);
              return;
            }
            break;
        }
        dataIndex++;
      });
    });
  };

  (function(){
    var slider = document.getElementById('slider1');
    var output = document.getElementById('slider1o');
    var start = document.getElementById('start');
    var animeSpeed = document.getElementById('anime-speed');
    var _isRunning = false;
    var _animationID;

    var input = slider.getElementsByTagName('input')[0];
    var root = document.documentElement;
    var dragging = false;
    var value = output.value;// 初期位置
    var width = input.clientWidth / 2;
    let frame = 0;

    var set_value = function (){
      // つまみのサイズ(input.clientWidth)だけ位置を調整
if(loadedFlg){
      input.style.left = (value - input.clientWidth/2) + 'px';
      output.value = value;
} else {
      value = 0;
      output.value = 0;
}
    };
    set_value();

    var autoUpdate = function () {
      var tmp = Number(output.value) + 1;
      if(tmp > TURN){
        _isRunning = false;
        start.innerText = '▶';
        cancelAnimationFrame(_animationID);
        output.value = 0;
        return;
      }
      _animationID = requestAnimationFrame(autoUpdate);
      frame++;
      if(frame % (50 - Number(animeSpeed.value)) !== 0) { return; }
      output.value = tmp;
      value = output.value;
      //renderMap(datalist[output.value]);
      renderMap(output.value);
      set_value();
    }

    // スタートボタンクリック
    start.onclick = function(evt){
      if (_isRunning) {
        _isRunning = false;
        start.innerText = '▶';
        cancelAnimationFrame(_animationID);
      } else if(loadedFlg){
       _isRunning = true;
        start.innerText = '■';
        autoUpdate();
      } else {
        if(inputFlg && outputData.length == TURN){
          $ ('#input').val(''); $('#output').val('');
          simulate();
          if(loadedFlg){
            _isRunning = true;
            start.innerText = '■';
            autoUpdate();
          }
        }
      }
    };

    // 目盛り部分をクリックしたとき
    slider.onclick = function(evt){
      dragging = true;
      document.onmousemove(evt);
      document.onmouseup();
    };
    // 数値の変更
    output.onchange = function(evt){
      value = evt.target.value;
      //renderMap(datalist[evt.target.value]);
      renderMap(evt.target.value);
    };
    // ドラッグ開始
    input.onmousedown = function(evt){
      dragging = true;
      return false;
    };
    // ドラッグ終了
    document.onmouseup = function(evt){
      if (dragging) {
        dragging = false;
        output.value = value;
        //renderMap(datalist[value]);
        renderMap(value);
      }
    };
    document.onmousemove = function(evt){
      if(dragging){
        // ドラッグ途中
        if(!evt){
          evt = window.event;
        }
        var left = evt.clientX;
        var rect = slider.getBoundingClientRect();
        // マウス座標とスライダーの位置関係で値を決める
        value = Math.round(left - rect.left - width);
        // スライダーからはみ出したとき
        if (value &lt; 0) {
          value = 0;
        } else if (value > slider.clientWidth) {
          value = slider.clientWidth;
        }
        set_value();
        return false;
      }
    };
    })();

## 输入格式

入力は以下の形式で与えられる。

> $ A_{1,1} $$ A_{1,2} $ ... $ A_{1,N} $ $ A_{2,1} $$ A_{2,2} $ ... $ A_{2,N} $ : $ A_{N,1} $$ A_{N,2} $ ... $ A_{N,N} $

- $ A_{y,x} $ は、マス $ (x,y) $ の初期状態を表し、`.`が更地、`#`が岩、`W`がワープゲートを表す。

## 输出格式

毎ターンの高橋君の行動を、$ 1000 $ 行で出力せよ。 各行動は、`コマンド 座標指定` の順で行う。各コマンドの出力方法については、各行動についての記述に従う。

## 说明/提示

### 道路の作成

> road $ X_1 $ $ Y_1 $ $ X_2 $ $ Y_2 $

上下または左右の直線に道路を作る。$ X_1=X_2 $ または $ Y_1=Y_2 $ を満たす必要があり、満たさない場合は `WA` となる。 岩やワープゲートが間にあるとそこには道路が出来ないが、畑は道路となり、畑にあるツカモは破棄される。 道路の作成には、長さの $ 2 $ 乗分のお金がかかる。岩やワープゲートや道路も長さに含まれる。 お金が払えない場合は、道路は作成されない。

### ツカモを植える

> plant $ X $ $ Y $

更地か畑のマスのツカモを $ 1 $ 増やす。更地・畑以外のマスだった場合は無視される。

### 収穫

> harvest $ X_1 $ $ Y_1 $ $ X_2 $ $ Y_2 $

長方形の範囲を指定してツカモを収穫する。収穫は左上のマスから順番に行われる。畑以外のマスは無視され、労働力を消費しない。 あるマスのツカモの収穫には、$ (そのマスへの移動距離\ -\ 10) $ だけの労働力を消費する。労働力が足りないマスは無視される。 ツカモが収穫されたマスは更地になる。ツカモを収穫すると、一本につき１円が得られる。 （移動距離については後述）

### 更地化

> destroy $ X_1 $ $ Y_1 $ $ X_2 $ $ Y_2 $

区間を指定して左上から順番に全て更地にする。道路・岩・畑は全て更地になるが、ワープゲートは無視され、お金を消費しない。 左上から順番に更地化していく。マス１つ１つに対し、そのマスへの移動距離と同じだけお金がかかる。 お金が足りない場合は何も行われない。元々更地の場合は無視される。 （移動距離については後述）

### 労働力のアップ

> growup $ A $

お金を使って労働力を $ A $ 増やす。 労働力の初期値は $ 100 $で、労働力を $ A $ 増やすのに、$ A*A $ 円かかる。 お金が足りない場合は、増やすことが可能な最大値が自動的に選択される。

### ワープゲート作成

> warpgate $ X $ $ Y $

マス $ (X,Y) $ にワープゲートを建築する。 お金が $ 1000 $ かかる。 指定したマスが更地、畑、道路以外の場合は無視され、お金もかからない。

### アルバイト

```
work
```

お金が $ 1 $ 増える。

### 移動距離の計算方法について

更地化、収穫の計算に使われる移動距離は、そのターンの開始時における、ワープゲートからそのマスへの最短経路で計算されます。 ワープゾーンを移動距離 $ 0 $ として、そこから上下左右の各マスに移動できます。 各マスに移動するためのコストは、移動するマスが道路だった場合は $ 1 $、岩だった場合は $ 50 $、その他の場合は $ 10 $ かかります。

### 区間の指定について

> $ X_1 $ $ Y_1 $ $ X_2 $ $ Y_2 $

上記の指定があった場合、マス $ (X_1,\ Y_1) $ とマス $ (X_2,\ Y_2) $ を端点とした、長方形領域に対して処理を行います。 $ X_1\ ≦\ X_2 $ および $ Y_1\ ≦\ Y_2 $ を満たす必要があります。 左上から順番に処理を行い、コストが足りないマスについては無視されます。上にあるマスほど優先され、$ Y $ 座標が同じ場合は、左にあるマスほど優先されます。

### 各ターンの進行について

各ターンは、以下の順番で進行します。

- 高橋君の行動の反映
- ツカモの成長

例えば、`plant`コマンドでツカモを植えた時、植えた後にツカモが成長するため、次のターンでそのマスのツカモは $ 2 $ に増加していることなどに注意してください。

### 行動まとめ

行動をまとめると以下のようになります。なお、「お金」もしくは「労働力」をまとめて「コスト」と表現しています。

![行動まとめ表](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_future_contest_2018_final_a/bd305b460aac0afee095e28c73736005c3181a5a.png)

### 各ターンの進行

### 制約

- $ N\ =\ 50 $
- 入力は、各マスに対し、$ 15パーセント $ が岩、残りは更地になるようにランダムで生成される。その後、マスの $ 1 $ つをランダムに選び、そのマスをワープゲートとする。

### 採点方法

$ 1 $ つのテストケースごとに、ツカモの収穫数が個別スコアとなります。

$ 50 $ つのテストケースの個別スコアの総和が、そのプログラムのスコアになります。

なお、 $ 1 $ ケースでも、出力の正しくない提出があった場合、example以外の点数は全て $ 0 $ 点となります。

### ビジュアライザー

入力ファイルと出力ファイルから、点数の計算およびターン毎の結果を可視化するビジュアライザを用意しました。

- このビジュアライザはchromeでの使用を推奨します。他の環境で正常に動作することを保証していません。特にInternet Explorerでは動作しないことを確認しています。
- このビジュアライザから解答の提出はできません。 AtCoder 上で解答を提出して下さい。
- このビジュアライザ上で計算された点数は、当コンテスト上での点数を保証するものではありません。このビジュアライザを使用することによるあらゆる損害は保障しかねますので、予めご了承ください。

### Sample Explanation 1

\[入力ファイルはこちらから(zip)\](https://img.atcoder.jp/future-contest-2018-final/48ad0fab78bb7d0722addfab890402ee.zip) 採点結果の「example\\\_01」「example\\\_02」「example\\\_03」が、こちらのデータとなります。このデータも採点対象となります。 \*\*決勝上位5名のexample\\\_01に対する\[出力ファイルはこちらから(zip)\](https://img.atcoder.jp/future-contest-2018-final/result.zip)\*\*

## 样例 #1

### 输入

```

```

### 输出

```
None
```

