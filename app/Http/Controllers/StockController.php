<?php


namespace App\Http\Controllers;

use Faker\Provider\Image;
use Illuminate\Http\Request;
use App\Portfolio;
use App\Stock;
use App\Providers\drawChart;

//use App\Http\Controllers\pData;
//use App\Http\Controllers\pDraw;
//use App\Http\Controllers\pImage;
// use App\Http\Controllers\pScatter;


class StockController extends Controller
{


    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {

        return view('stocks.index');
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        return view('stocks.create', compact('portfolio'));
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        $stock = new Stock;

        $stock->portfolio_id = $request->id;

        $stock->ticker = $request->ticker;

        $stock->save();


        $equitys = Stock::where('portfolio_id', $request->id)->get();
        $list = '';
        $symbol = '';
        $id = $request->id;
        $stock_ids = [];

        if (!$equitys->isEmpty()) {
            foreach ($equitys as $equity) {
                array_push($stock_ids, $equity->id);
                $ticker = $equity->ticker;
                if ($equity == $equitys->last()) {
                    $list = $list . $ticker;
                } else {
                    $list = $list . $ticker . '+';
                }

            }

        }

        // Get stocks data from yahoo
        $f = fopen("http://finance.yahoo.com/d/quotes.csv?s=". $list . "&f=xsnopp2", "r");
        $stocksArray =[];
        $markets = '';
        while (($line = fgetcsv($f)) !== false){
            array_push($stocksArray, $line);
            $markets = $markets . $line[0] . ',';
        }
        $markets = trim($markets, ',');




        return view('stocks.show', compact('symbol', 'list', 'id', 'stock_ids', 'stocksArray', 'markets'));
    }

    /**
     * Display the specified resource.
     *
     * @param  int $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        // return view('stocks.show');
        $stocks = Stock::where('portfolio_id', $id)->get();
        $list = '';
        $symbol = '';
        $stock_ids = [];

        if (!$stocks->isEmpty()) {
            foreach ($stocks as $stock) {
                array_push($stock_ids, $stock->id);
                $ticker = $stock->ticker;
                if ($stock == $stocks->last()) {
                    $list = $list . $ticker;
                } else {
                    $list = $list . $ticker . '+';
                }

            }

        }

        // Get stocks data from yahoo
        $f = fopen("http://finance.yahoo.com/d/quotes.csv?s=". $list . "&f=xsnopp2", "r");
        $stocksArray =[];
        $markets = '';
        while (($line = fgetcsv($f)) !== false){
            array_push($stocksArray, $line);
            $markets = $markets . $line[0] . ',';
        }
        $markets = trim($markets, ',');




        return view('stocks.show', compact('symbol', 'list', 'id', 'stock_ids', 'stocksArray', 'markets'));

    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {

    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request $request
     * @param  int $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        //
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int $id
     * @return \Illuminate\Http\Response
     */
    public function destroy(Request $request, $id)
    {
        Stock::destroy($id);

        $equitys = Stock::where('portfolio_id', $request->id)->get();
        $list = '';
        $symbol = '';
        $id = $request->id;
        $stock_ids = [];

        if (!$equitys->isEmpty()) {
            foreach ($equitys as $equity) {
                array_push($stock_ids, $equity->id);
                $ticker = $equity->ticker;
                if ($equity == $equitys->last()) {
                    $list = $list . $ticker;
                } else {
                    $list = $list . $ticker . '+';
                }

            }

        }

        // Get stocks data from yahoo
        $f = fopen("http://finance.yahoo.com/d/quotes.csv?s=". $list . "&f=xsnopp2", "r");
        $stocksArray =[];
        $markets = '';
        while (($line = fgetcsv($f)) !== false){
            array_push($stocksArray, $line);
            $markets = $markets . $line[0] . ',';
        }
        $markets = trim($markets, ',');




        return view('stocks.show', compact('symbol', 'list', 'id', 'stock_ids', 'stocksArray', 'markets'));
    }

    public function find(Request $request, $id)
    {
        $market = $request->market_type;
        $ticker = $request->ticker;

        $symbol = $ticker . $market;

        // Get stock data from Yahoo
        $f = fopen("http://finance.yahoo.com/d/quotes.csv?s=". $symbol . "&f=xsnopp2", "r");
        $quoteArray = fgetcsv($f);

        $stocks = Stock::where('portfolio_id', $id)->get();
        $list = '';
        $stock_ids = [];

        if (!$stocks->isEmpty()) {
            foreach ($stocks as $stock) {
                array_push($stock_ids, $stock->id);
                $ticker = $stock->ticker;
                if ($stock == $stocks->last()) {
                    $list = $list . $ticker;
                } else {
                    $list = $list . $ticker . '+';
                }

            }

        }

        // Get stocks data from yahoo
        $f = fopen("http://finance.yahoo.com/d/quotes.csv?s=". $list . "&f=xsnopp2", "r");
        $stocksArray =[];
        $markets = '';
        while (($line = fgetcsv($f)) !== false){
            array_push($stocksArray, $line);
            $markets = $markets . $line[0] . ',';
        }
        $markets = trim($markets, ',');




        return view('stocks.show', compact('symbol', 'list', 'id', 'stock_ids', 'quoteArray', 'stocksArray', 'markets'));

    }

    public function build(Request $request)
    {

        $id = $request->id;
        $marketsString = $request->markets;
        $stocks = Stock::where('portfolio_id', $id)->get();
        $tickers = [];
        $markets = [];
        $market = '';

        foreach ($stocks as $stock) {
            $ticker = $stock->ticker;
            $ticker = strtoupper($ticker);
            $find = '.';

            $pos = strpos($ticker, $find);

            if ($pos === false) {
                array_push($tickers, $ticker);
                array_push($markets, $market);
            } else {

                $code = substr($ticker, 0, $pos);
                array_push($tickers, $code);
                $exchange = substr($ticker, $pos + 1);
                switch ($exchange) {

                    case 'L':
                        array_push($markets, 'LON');
                        break;
                    case 'PA':
                        array_push($markets, 'EPA');
                        break;
                    case 'F':
                        array_push($markets, 'FRA');
                        break;
                }
            }
        }

        $returns = [];
        $prices = [];
        $averageReturns = [];
        for ($i = 0; $i < count($tickers); ++$i) {
            $f = fopen("http://www.google.com/finance/getprices?q=" . $tickers[$i] . "&x=" . $markets[$i] . "&i=86400&p=11d&f=o,c&df=cpct", "r");

            $lineNo = 0;
            $startLine = 8;
            $endLine = 29;
            //   for ($i = 8; $i < 18; $i++){
            //  $row = $f[8];
            //    $line = str_getcsv($row);
            // foreach ($f as $cell){
            //   array_push($quotes, $cell);
            //  }
            //   }
            $quotes = [];
            $averages = [];
            while (($line = fgetcsv($f)) !== false) {
                $lineNo++;


                if ($lineNo >= $startLine) {
                    foreach ($line as $cell) {
                        $num = (float)$cell;
                        array_push($quotes, $num);
                        array_push($prices, $num);
                    }
                }
                if ($lineNo == $endLine) {
                    break;
                }


            }

            for ($j = 0; $j < 10; $j++) {

                $change = (($quotes[0] - $quotes[1]) / $quotes[1] * 100);
                array_push($returns, $change);
                array_push($averages, $change);
                array_shift($quotes);
                array_shift($quotes);
            }

            $average = array_sum($averages) / count($averages);
            array_push($averageReturns, $average);
            fclose($f);
// $lines = fgetcsv($f);
        }
        $tickersList = '';
        $returnsList = '';
        $averageReturnsList = '';

        foreach ($tickers as $ticker) {

            if ($ticker == end($tickers)) {
                $tickersList = $tickersList . $ticker;
            } else {
                $tickersList = $tickersList . $ticker . ',';
            }
        }

        foreach ($returns as $return) {

            if ($return == end($returns)) {
                $returnsList = $returnsList . $return;
            } else {
                $returnsList = $returnsList . $return . ',';
            }
        }
        foreach ($averageReturns as $averageReturn) {

            if ($averageReturn == end($averageReturns)) {
                $averageReturnsList = $averageReturnsList . $averageReturn;
            } else {
                $averageReturnsList = $averageReturnsList . $averageReturn . ',';
            }
        }

        $file = "frontier.jl";
        $this->runJuliaFile($file, $returnsList, $averageReturnsList, $tickersList);

        //$command = print_r($frontier,true);
        $command = file_get_contents('output.txt');

        $file = fopen('output.txt', 'r');
        $count = 0;
        $return = [];
        $risk = [];
        while (($line = fgetcsv($file)) !== false) {

            $count++;
            if ($count > 1) {
                $return = $line;
            } else {
                $risk = $line;
            }
        }


        $frontierGraph = new drawChart();
        $frontierGraph->graph($return, $risk);

        /*$image = Image::make(file_get_contents('chart.png'));
        $image->encode('png');
        $type = 'png';
        $base64 = 'data:image/' . $type . ';base64,' . base64_encode($image);*/
        $image = asset('chart.png');


        return view('stocks.index', compact('tickers', 'markets', 'prices', 'tickersList', 'returnsList', 'averageReturnsList', 'command', 'return', 'id', 'image', 'marketsString'));

    }

    public function runJuliaFile($file, $returns, $averages, $tickers)
    {

        ini_set('display_errors', 1);
        ini_set('display_startup_errors', 1);
        error_reporting(E_ALL);

        $connection = ssh2_connect('ec2-34-249-101-43.eu-west-1.compute.amazonaws.com', 22);
        if (
        ssh2_auth_password($connection, 'public', 'PubFi$h412')
        ) {
            echo "Authentication success";
        } else {
            die('Authentication failed');
        }
        $command = "julia " . $file . " " . $returns . " " . $averages . " " . $tickers;
        //$command = "julia outputTest.jl {$returns} {$averages} {$tickers}";

        ssh2_exec($connection, $command);
        // $text = stream_get_contents($message);
        //$message = `ls`;
        //$result = shell_exec($command);
        // header('Location: http://ec2-34-249-101-43.eu-west-1.compute.amazonaws.com/buildfrontier/');
        // return $text;
        //return $result;
    }

    /* public function drawFrontierGraph(){


               $return = array(2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.97,3.92,5.49,7.67,10.47,13.89,17.93);
         $risk = array(4.76,9.52,14.28,19.04,23.80,28.57,33.33,38.09,42.85,47.61,52.38,57.14,61.90,66.66,71.42,76.19,80.95,85.71,90.47,95.23);

         // Create and populate the pData object
         $frontierData = new pData();
         // x axis
         $frontierData->addPoints($risk,"Risk");
         $frontierData->addPoints(array(2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.64,2.97,3.92,5.49,7.67,10.47,13.89,17.93),"Risk");
         $frontierData->setAxisName(0,"Risk");
         $frontierData->setAxisXY(0,AXIS_X);
         $frontierData->setAxisPosition(0,AXIS_POSITION_BOTTOM);

         // y axiz
         $frontierData->addPoints($return,"Return");
         $frontierData->addPoints(array(4.76,9.52,14.28,19.04,23.80,28.57,33.33,38.09,42.85,47.61,52.38,57.14,61.90,66.66,71.42,76.19,80.95,85.71,90.47,95.23),"Return");
         $frontierData->setSerieOnAxis("Return",1);
         $frontierData->setAxisName(1,"Return");
         $frontierData->setAxisXY(1,AXIS_Y);

         // Set scatter line series
         $frontierData->setScatterSerie("Risk", "Return",0);
         $frontierData->setScatterSerieDescription(0,"Efficiency frontier");
         $frontierData->setScatterSerieColor(0,array("R"=>0,"G"=>0,"B"=>0));

         // Create the pChart object
         $frontierPicture = new pImage(800,600,$frontierData);

         // Overlay with a gradient
         $Settings = array("StartR"=>50, "StartG"=>50, "StartB"=>170, "EndR"=>100, "EndG"=>100, "EndB"=>250, "Alpha"=>70);
         $frontierPicture->drawGradientArea(0,0,800,600,DIRECTION_VERTICAL,$Settings);
         $frontierPicture->drawGradientArea(0,0,800,30,DIRECTION_VERTICAL,array("StartR"=>20,"StartG"=>20,"StartB"=>100,"EndR"=>70,"EndG"=>70,"EndB"=>250,"Alpha"=>80));

         // Add a border to the picture
         $frontierPicture->drawRectangle(0,0,799,599,array("R"=>0,"G"=>0,"B"=>0));

         // Write the picture title
         $frontierPicture->setFontProperties(array("FontName"=>"pChart2.1.4/fonts/GeosansLight.ttf","FontSize"=>14));
         $frontierPicture->drawText(10,25,"Portfolio: Title",array("R"=>255,"G"=>255,"B"=>255));

         // Write the chart title
         $frontierPicture->setFontProperties(array("FontName"=>"pChart2.1.4/fonts/GeosansLight.ttf","FontSize"=>14));
         $frontierPicture->drawText(180,70,"Efficiency Frontier",array("FontSize"=>24,"Align"=>TEXT_ALIGN_BOTTOMMIDDLE));

         // Draw the scale and the 1st chart
         $frontierPicture->setGraphArea(60,80,760,500);
         $frontierPicture->drawFilledRectangle(60,80,760,500,array("R"=>255,"G"=>255,"B"=>255,"Surrounding"=>-200,"Alpha"=>10));
         $frontierPicture->setShadow(TRUE,array("X"=>1,"Y"=>1,"R"=>0,"G"=>0,"B"=>0,"Alpha"=>10));
         $frontierPicture->setFontProperties(array("FontName"=>"pChart2.1.4/fonts/GeosansLight.ttf","FontSize"=>14));

         // Draw Scatter
         $frontierScatter = new pScatter($frontierPicture,$frontierData);
         $frontierScatter->drawScatterScale();
         $frontierScatter->drawScatterPlotChart();

         // Write the chart legend
         $frontierScatter->drawScatterLegend(50,550,array("Style"=>LEGEND_NOBORDER,"Mode"=>LEGEND_HORIZONTAL));

         // Render the picture (choose the best way)
         $frontierPicture->autoOutput("pictures/example.drawScatterPlotChart.png");
     }*/
}
