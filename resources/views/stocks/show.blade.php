@extends('layouts.app')

@section('title')
    Build Portfolio
@endsection

@section('content')
    <style>
        table {
            font-family: arial, sans-serif;
            border-collapse: collapse;
            width: 100%;
        }

        td, th {
            border: 1px solid #dddddd;
            text-align: left;
            padding: 8px;
        }


    </style>
    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading"><h3>Build Portfolio</h3></div>
                    <div class="panel-body">
                        <form method="post" action="/findstocks/{{ $id }}">
                            {{ csrf_field() }}
                            <div class="form-group">
                                <label for="market_type" class="col-md-1">Market</label>
                                <div class="col-md-6">
                                    <select id="market_type" type="text" class="form-control" name="market_type"
                                            list="market_type">
                                        <option id="DOW" value="">New York Stock Exchange, United States</option>
                                        <option id="NASDAQ" value="">NASDAQ, United States</option>
                                        <option id="FTSE" value=".L">London Stock Exchange, United Kingdom</option>
                                        <option id="Cac 40" value=".PA">Paris Stock Exchange, France</option>
                                        <option id="DAX" value=".F">Frankfurt Stock Exchange, Germany</option>
                                    </select>
                                </div>
                                <label for="ticker" class="col-md-1">Ticker</label>
                                <div class="col-md-2">
                                    <input id="ticker" type="text" class="form-control" name="ticker">
                                </div>
                                <button type="submit" class="btn btn-success pull-right">Find Stock</button>
                            </div>

                        </form>
                    </div>
                </div>
            </div>
        </div>
    </div>



    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading"><h3>Stock search results</h3></div>
                    <div class="panel-body">

                        @if (!$symbol == "")
                            <table>
                                <tr>
                                    <th>Exchange</th>
                                    <th>Symbol</th>
                                    <th>Name</th>
                                    <th>Open</th>
                                    <th>Close</th>
                                    <th>Change</th>
                                    <th>Remove</th>


                                @php($f = fopen("http://finance.yahoo.com/d/quotes.csv?s=". $symbol . "&f=xsnopp2", "r"))

                                @while (($line = fgetcsv($f)) !== false)
                                    <tr>
                                        @foreach ($line as $cell)
                                            <td>
                                                @php
                                                    echo $cell
                                                @endphp
                                            </td>

                                        @endforeach
                                        <td>
                                            <form method="post" action="/stocks">
                                                {{ csrf_field() }}

                                                <input type="hidden" name="id" value="{{ $id }}">
                                                <input type="hidden" name="ticker" value="{{ $symbol }}">
                                                <button type="submit" class="btn btn-success pull-right">Add
                                                </button>
                                            </form>
                                        </td>
                                    </tr>

                                @endwhile
                                @php(fclose($f))


                            </table>
                        @else
                            <h4>Use the form above to enter a stocks market and ticker details. Pressing find stock will
                                show the stock details</h4>
                        @endif

                    </div>
                </div>
            </div>
        </div>
    </div>

    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading"><h3>Stocks in portfolio</h3></div>
                    <div class="panel-body">

                        @if (!$list == "")
                            <table>
                                <tr>
                                    <th>Exchange</th>
                                    <th>Symbol</th>
                                    <th>Name</th>
                                    <th>Open</th>
                                    <th>Close</th>
                                    <th>Change</th>
                                    <th>Add</th>


                                @php($f = fopen("http://finance.yahoo.com/d/quotes.csv?s=". $list . "&f=xsnopp2", "r"))
                                @php($count = 0)
                                @while (($line = fgetcsv($f)) !== false)
                                    @php($stock = $stock_ids[$count])


                                    <tr>
                                        @foreach ($line as $cell)
                                            <td>
                                                @php
                                                    echo $cell
                                                @endphp
                                            </td>

                                        @endforeach
                                        <td>
                                            <form method="post" action="/stocks/{{ $stock }}">
                                                {{ method_field('DELETE') }}
                                                {{ csrf_field() }}

                                                <input type="hidden" name="id" value="{{ $id }}">
                                                <input type="hidden" name="ticker" value="{{ $symbol }}">
                                                <input type="submit" class="btn pull-right btn-danger"
                                                       onclick="return confirm('Are you sure you want to delete this stock?');"
                                                       name="name"
                                                       value="Remove">
                                            </form>
                                        </td>
                                    </tr>
                                    @php($count++)
                                @endwhile
                                @php(fclose($f))


                            </table>
                        @else
                            <h4>
                                There are currently no stocks in the portfolio, use the add button to add stocks to the
                                portfolio.
                            </h4>
                        @endif
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-body">
                        <form action="/stocks" method="get">
                            <a href="{{ url('/portfolios') }}" class="btn btn-primary">Return to Portfolios</a>
                            <button type="submit" class="btn btn-success pull-right" onclick="resultTest.php">Show Efficency Frontier</button>
                        </form>
                    </div>
                </div>
            </div>
        </div>
    </div>
@endsection