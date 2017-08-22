@extends('layouts.app')

@section('title')
    Optimised Portfolio
@endsection

@section('content')

    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading panel-title">
                        Optimised Portfolio
                    </div>

                    <div class="panel-body">
                        <table class="table table-bordered table-condensed">
                            <tr>
                                <th>Market</th>
                                <th>Stock Ticker</th>
                                <th>Percentage to invest in Stock</th>
                            </tr>
                            @foreach($tableArray as list($a, $b, $c))
                                <tr>
                                    <td>{{ $a }}</td>
                                    <td>{{ $b }}</td>
                                    <td class="text-center">{{ round($c,2) * 100 }}</td>
                                </tr>
                            @endforeach
                        </table>

                    </div>
                    <div class="panel-body">
                        <label class="alert alert-info">Risk: {{ $risk }}</label>
                        <label class="alert alert-info">Investment: {{ $investment }}</label>
                        <label class="alert alert-info">Expected Return: {{ $return }}</label>
                    </div>
                </div>
            </div>
        </div>
    </div>


    {{--<p>{{ $id }}</p>
    <p>{{ $return }}</p>
    <p>{{ $result }}</p>
    @foreach($array as $value)
        <p>{{ round($value,2)*100 }}</p>
    @endforeach

    <p>{{ $test }}</p>
    <div>

        <p>Tickers: {{ $tickers }}</p>

    </div>
    <div>

        <p style="word-wrap: break-word">Returns: {{ $data }}</p>

    </div>

    <div>
        <p>Average Returns: {{ $returns }}</p>
    </div>--}}
    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading panel-title">
                        Save Optimisation
                    </div>
                    <div class="panel-body">
                        <form class="form-horizontal" role="form" action="/make" method="post">
                            {{ csrf_field() }}

                            <input type="hidden" name="id" value="{{ $id }}">
                            <input type="hidden" name="return" value="{{$return}}">
                            <input type="hidden" name="risk" value="{{ $risk }}">
                            <input type="hidden" name="investment" value="{{ $investment }}">
                            {{--<input type="hidden" name="returnsList" value="{{ $data }}">
                            <input type="hidden" name="averageReturnsList" value="{{ $returns }}">
                            <input type="hidden" name="tickersList" value="{{ $tickers }}">--}}
                            <input type="hidden" name="tableArray" value="{{ serialize($tableArray) }}">
                            <div class="form-group{{ $errors->has('name') ? ' has-error' : '' }}">
                                <label for="name" class="col-md-4 control-label">Optimisation Name</label>

                                <div class="col-md-8">
                                    <input id="name" type="text" class="form-control" name="name"
                                           value="{{ old('name') }}" required autofocus>

                                    @if ($errors->has('name'))
                                        <span class="help-block">
                                        <strong>{{ $errors->first('name') }}</strong>
                                    </span>
                                    @endif
                                </div>
                            </div>

                            <div class="form-group{{ $errors->has('description') ? ' has-error' : '' }}">
                                <label for="description" class="col-md-4 control-label">Optimisation Description</label>

                                <div class="col-md-8">
                                    <input id="description" type="text" class="form-control" name="description"
                                           required>

                                    @if ($errors->has('description'))
                                        <span class="help-block">
                                        <strong>{{ $errors->first('description') }}</strong>
                                    </span>
                                    @endif
                                </div>
                            </div>
                            <div class="form-group">
                                <div class="col-md-12">

                                    <a class="btn btn-danger" href="/buildfrontier/{{ $id }}/{{ $markets }}">Cancel</a>
                                    <button type="submit" class="btn btn-success pull-right">Save Optimisation</button>
                                </div>
                            </div>
                        </form>
                        {{--<form action="/buildfrontier" method="post">
                            {{ csrf_field() }}
                            <button type="submit" class="btn btn-primary pull-left">Cancel
                            </button>
                            <input type="hidden" name="id" value="{{ $id }}">
                            <input type="hidden" name="returnsList" value="{{ $data }}">
                            <input type="hidden" name="averageReturnsList" value="{{ $returns }}">
                            <input type="hidden" name="tickersList" value="{{ $tickers }}">
                        </form>--}}
                    </div>
                </div>
            </div>
        </div>
    </div>
@endsection