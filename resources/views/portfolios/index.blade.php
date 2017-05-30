@extends('layouts.app')

@section('title')
    My Portfolios
@endsection

@section('content')
    <div class="container">
        <div class="row-marketing">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading">My Portfolios</div>
                    <ul class="list-group">
                        @forelse($portfolios as $portfolio)
                            <li class="list-group-item" style="margin-top: 20px">

                    <span>
                        <h4>Name: {{ $portfolio->name }}</h4>
                        <h4>Description: {{ $portfolio->description }}</h4>

                        <p>Created ({{ $portfolio->created_at->diffForHumans() }})</p>

                    </span>

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
                            </li>
                        @empty
                            <h4>You have no portfolios</h4>
                            <form method="get" action="{{ url('/portfolios/create') }}">
                                {{ csrf_field() }}
                                <button type="submit" class="btn btn-primary">Create Portfolio</button>

                            </form>
                        @endforelse
                        {{ $portfolios->links() }}
                    </ul>
                </div>
            </div>
        </div>
    </div>
@endsection