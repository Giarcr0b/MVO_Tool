@extends('layouts.app')

@section('title')
    Home
@endsection

@section('content')
    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading panel-title">Welcome {{ Auth::user()->name }}: You are logged in!</div>
                    
                    <div class="panel-body">
                        <form method="get" action="{{ url('/portfolios/create') }}">
                            {{ csrf_field() }}
                            <a href="{{ url('/portfolios') }}" class="btn btn-primary">My Portfolios</a>
                            <button type="submit" class="btn btn-success pull-right">Create Portfolio</button>
                        </form>

                    </div>
                </div>
            </div>
        </div>
    </div>
@endsection
