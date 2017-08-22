@extends('layouts.app')
<!-- Style for range labels -->
<style>

    .range-labels {
        margin: 18px -41px 0;
        padding: 0;
        list-style: none;
    }

    li {
        position: relative;
        float: left;
        width: 90.25px;
        text-align: center;
        font-size: 14px;
        cursor: pointer;
    }

    .active {
        color: #37adbf;
    }

    .selected {
        background: #37adbf;
    }

    .active.selected {
        display: none;
    }


</style>
@section('title')
    Chart View
@endsection

@section('content')

    <div class="container">
        <div class="row">
            <div class="col-lg-10 col-lg-offset-1">
                <div class="panel panel-default">
                    <div class="panel-heading panel-title">
                        Frontier Graph
                    </div>
                    <div class="panel-body">


                        {{--<img src="chart.png">--}}
                        <img src="{{ $image }}" alt="Frontier Graph" style="margin: auto; display: block">


                    </div>

                </div>

            </div>

        </div>

    </div>


    <div class="container">
        <div class="row">
            <div class="col-md-10 col-md-offset-1">
                <div class="panel panel-default">
                    <div class="panel-heading panel-title">
                        Optimise Portfolio
                    </div>
                    <div class="panel-body">

                        <datalist id="powers">
                            @foreach($return as $num)
                                <option value="{{ round($num, 4) }}">
                            @endforeach
                        </datalist>
                        <p>Use the form below to select a return value and an investment amount before pressing the
                            optimise portfolio button.</p>
                        <ul class="range-labels">
                            @foreach($return as $item)
                                <li>{{ $item }}%</li>
                            @endforeach
                        </ul>
                        <form method="post" action="{{url('/optimisations')}}">
                            <div class="range">
                                <input id="slider2" type="range" min="{{ $return[0] }}" max="{{ $return[10] }}"
                                       step="{{ round($return[10]/100,4) }}" list="powers" value="{{ $return[5] }}"
                                       oninput="showValue(this.value)" name="slider"/>
                            </div>


                            <div class="form-group">
                                <label class="btn btn-info">Desired Return: <span
                                            id="range">{{ $return[5] }}</span></label>
                            </div>
                            <div class="form-group">
                                <label class="btn btn-info" for="invest">Investment Amount:</label>
                                <input id="invest" class="input" type="number" min="0" max="100000" step="100"
                                       name="investment" value="0">

                            </div>
                            <div class="form-group">
                                <a href="/stocks/{{ $id }}" class="btn btn-primary">Return to Portfolio</a>


                                <script type="text/javascript">
                                    function showValue(newValue) {
                                        document.getElementById("range").innerHTML = newValue;
                                    }
                                </script>

                                {{ csrf_field() }}
                                <button type="submit" class="btn btn-success pull-right">
                                    Optimise Portfolio
                                </button>

                                <input type="hidden" name="id" value="{{ $id }}">
                                <input type="hidden" name="data" value="{{ $returnsList }}">
                                <input type="hidden" name="returns" value="{{ $averageReturnsList }}">
                                <input type="hidden" name="tickers" value="{{ $tickersList }}">
                                <input type="hidden" name="markets" value="{{ $marketsString }}">
                            </div>
                        </form>
                    </div>

                </div>

            </div>

        </div>
    </div>

    </div>


@endsection