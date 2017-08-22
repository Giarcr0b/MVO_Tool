@extends('layouts.app')

@section('title')
    Optimisations
@endsection

@section('content')
    {{--<style>
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


    </style>--}}
    <div class="container">
        <div class="row-marketing">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading">Optimisations for {{ $name }} Portfolio</div>
                </div>
            </div>
        </div>
    </div>
    @foreach($optimisations as $optimisation)
        <div class="container">
            <div class="row-marketing">
                <div class="col-md-8 col-md-offset-2">
                    <div class="panel panel-default">
                        <div class="panel-heading">Name: {{ $optimisation->name }}</div>
                        <div class="panel-body">
                            <p>Description: {{ $optimisation->description }}</p>

                            @php($tableArray = unserialize($optimisation->data_file))
                            <table class="table table-bordered table-condensed">
                                <tr>
                                    <th>Market</th>
                                    <th>Stock</th>
                                    <th>Weight</th>
                                </tr>
                                @foreach($tableArray as list($a, $b, $c))
                                    <tr>
                                        <td>{{ $a }}</td>
                                        <td>{{ $b }}</td>
                                        <td>{{ round($c,2) * 100 }}</td>
                                    </tr>
                                @endforeach

                            </table>
                        </div>
                        <div class="panel-body">
                            <label class="alert alert-info">Risk: {{ $optimisation->risk }}</label>
                            <label class="alert alert-info">Expected Return: {{ $optimisation->return }}</label>
                            <label class="alert alert-info">Investment Amount: {{ $optimisation->investment }}</label>

                        </div>
                        <div class="panel-body">
                            <form class="form-horizontal" role="form" method="POST"
                                  action="/optimisations/{{ $optimisation->id }}">

                                <input name="method" type="hidden" value="delete">
                                {{ method_field('DELETE') }}
                                {{ csrf_field() }}
                                <a href="/stocks/{{ $optimisation->portfolio_id }}"
                                   class="btn btn-primary">Return to Portfolio</a>
                                <a href="/optimisations/{{ $optimisation->id }}/edit"
                                   class="btn btn-primary">Edit</a>

                                <input type="submit" class="btn pull-right btn-danger"
                                       onclick="return confirm('Are you sure you want to delete this optimisation?');"
                                       name="name"
                                       value="Delete">

                            </form>

                        </div>
                    </div>
                </div>
            </div>
        </div>
    @endforeach


@endsection