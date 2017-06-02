<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Portfolio;
use App\Stock;

class StockController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {

        $myfilename = "output.txt";
        if (file_exists($myfilename)) {
            $result = file_get_contents($myfilename);
        }
        return 'hello';
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


        return view('stocks.show', compact('symbol', 'list', 'id', 'stock_ids'));
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


         return view('stocks.show', compact('symbol', 'list', 'id', 'stock_ids'));

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


        return view('stocks.show', compact('symbol', 'list', 'id', 'stock_ids'));
    }

    public function find(Request $request, $id)
    {
        $market = $request->market_type;
        $ticker = $request->ticker;

        $symbol = $ticker . $market;

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
        return view('stocks.show', compact('symbol', 'list', 'id', 'stock_ids'));

    }
}
