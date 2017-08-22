<?php

namespace App\Http\Controllers;

use App\Portfolio;
use Illuminate\Http\Request;
use App\Stock;
use App\Optimisation;
use phpDocumentor\Reflection\Types\Array_;

class OptimisationController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        //
return "hello";
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        //
        return "hello create";
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        //
        $id = $request->id;
        $return = $request->slider;
        $data = $request->data;
        $returns = $request->returns;
        $tickers = $request->tickers;
        $markets = $request->markets;
        $investment = $request->investment;
        $file = "MVOtest.jl";
        $this->runMVOFile($file, $data, $returns, $tickers, $return);

        $result = file_get_contents('output.txt');
        $replace = array('(','[',']',')');
        $result = str_replace($replace,'',$result);
        $weightsArray = str_getcsv($result);
        $tickersArray = str_getcsv($tickers);
        $marketsArray = str_getcsv($markets);
        $risk = round(array_shift($weightsArray),4) * 100;

        $tableArray = array();
        for ($i=0; $i < count($weightsArray); $i++){
            $row = array();
            array_push($row, $marketsArray[$i]);
            array_push($row, $tickersArray[$i]);
            array_push($row, $weightsArray[$i]);
            array_push($tableArray, $row);
        }
        //$test = round($weightsArray[1],2) * 100;

        //$stocks = Stock::where('portfolio_id', $id)->get();

        return view('optimisations.store', compact('id', 'return', 'data', 'returns', 'tickers', 'result', 'risk', 'investment', 'tableArray', 'markets'));
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        //Get optimisation
        $optimisation = Optimisation::findOrFail($id);
        //Get portfolio id
        $portfolioId = $optimisation->portfolio_id;
        // get portfolio name
        $portfolio = Portfolio::findOrFail($portfolioId);
        $name = $portfolio->name;

        //Get all optimisations for portfolio
        $optimisations = Optimisation::where('portfolio_id', $portfolioId)->get();



        return view('optimisations.index', compact('optimisations', 'name'));


    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        //
        $optimisation = Optimisation::findOrFail($id);

        return view('optimisations.edit', compact('optimisation'));
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        // update optimisation with new data
        $optimisation = Optimisation::findOrFail($id);
        $optimisation->name = $request->name;
        $optimisation->description = $request->description;
        $optimisation->save();

        // Get portfolio id
        $portfolioId = $optimisation->portfolio_id;

        ////Get all optimisations for portfolio
        $optimisations = Optimisation::where('portfolio_id', $portfolioId)->get();

        //Get name of portfolio
        $portfolio = Portfolio::findOrFail($portfolioId);
        $name = $portfolio->name;

        return view('optimisations.index', compact('optimisations', 'name'));
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        //
        $optimisation = Optimisation::findOrFail($id);
        $portfolioId = $optimisation->portfolio_id;

        Optimisation::destroy($id);

        ////Get all optimisations for portfolio
        $optimisations = Optimisation::where('portfolio_id', $portfolioId)->get();

        //Get name of portfolio
        $portfolio = Portfolio::findOrFail($portfolioId);
        $name = $portfolio->name;



        return view('optimisations.index', compact('optimisations', 'name'));
    }

    public function runMVOFile($file, $data, $returns, $tickers, $return){

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
        $command = "julia " . $file . " " . $data . " " . $returns . " " . $tickers . " " . $return;

        ssh2_exec($connection, $command);
    }

public function make(Request $request){

// Create optimisation object and assign values
    $optimisation = new Optimisation;
    $optimisation->portfolio_id = $request->id;
    $optimisation->name = $request->name;
    $optimisation->description = $request->description;
    $optimisation->data_file = $request->tableArray;
    $optimisation->risk = $request->risk;
    $optimisation->return = $request->return;
    $optimisation->investment = $request->investment;

    //Save optimisation
    $optimisation->save();

    //Get all optimisations for portfolio
    $optimisations = Optimisation::where('portfolio_id', $request->id)->get();

    //Get name of portfolio
    $portfolio = Portfolio::findOrFail($request->id);
    $name = $portfolio->name;




    return view('optimisations.index', compact('optimisations', 'name'));
}
}
