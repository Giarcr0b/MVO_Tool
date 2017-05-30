@extends('layouts.app')

@section('title')
    Home
@endsection

@section('content')
    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading">Dashboard</div>

                    <div class="panel-body">
                        {{ Auth::user()->name }}: You are logged in!
                        <form method="get" action="{{ url('/portfolios/create') }}">
                            {{ csrf_field() }}
                            <button type="submit" class="btn btn-primary">Create Portfolio</button>

                            <a href="{{ url('/portfolios') }}" class="btn btn-primary">My Portfolios</a>
                        </form>

                    </div>
                </div>
            </div>
        </div>
    </div>
@endsection
