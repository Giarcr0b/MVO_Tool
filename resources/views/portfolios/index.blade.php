@extends('layouts.app')

@section('title')
    My Portfolios
@endsection

@section('content')
    <div class="container">
        <div class="row-marketing">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading panel-title">My Portfolios</div>
                </div>
            </div>
        </div>
    </div>
    @forelse($portfolios as $portfolio)
        <div class="container">
            <div class="row-marketing">
                <div class="col-md-8 col-md-offset-2">
                    <div class="panel panel-default">
                        <div class="panel-heading">Name: {{ $portfolio->name }}</div>
                        <div class="panel-body">
                            <h5>Description: {{ $portfolio->description }}</h5>
                            <p>Created ({{ $portfolio->created_at->diffForHumans() }})</p>
                        </div>
                        <div class="panel-body">
                            <form class="form-horizontal" role="form" method="POST"
                                  action="/portfolios/{{ $portfolio->id }}">
                                <input name="method" type="hidden" value="delete">
                                {{ method_field('DELETE') }}
                                {{ csrf_field() }}
                                <a href="/portfolios/{{ $portfolio->id }}/edit"
                                   class="btn btn-primary">Edit</a>
                                <a href="/stocks/{{ $portfolio->id }}"
                                   class="btn btn-primary">View</a>

                                <input type="submit" class="btn pull-right btn-danger"
                                       onclick="return confirm('Are you sure you want to delete this portfolio?');"
                                       name="name"
                                       value="Delete">
                            </form>
                        </div>
                    </div>
                </div>
            </div>
        </div>

    @empty
        <div class="container">
            <div class="row-marketing">
                <div class="col-md-8 col-md-offset-2">
                    <div class="panel panel-default">
                        <div class="panel-heading panel-title">You have no portfolios</div>
                        <div class="panel-body">
                            <form method="get" action="{{ url('/portfolios/create') }}">
                                {{ csrf_field() }}
                                <button type="submit" class="btn btn-primary">Create Portfolio</button>

                            </form>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    @endforelse
    {{ $portfolios->links() }}
@endsection